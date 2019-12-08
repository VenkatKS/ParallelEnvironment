#include "abstract_env.h"
#include "logger.h"

#include <omp.h>

std::vector<uint64_t> AbstractEnv::step (const std::vector<ActionType>& actions) {
    if (_current_backend == EnvBackend::SEQ) return seq_step(actions);
    return omp_step(actions);
}

std::vector<uint64_t> AbstractEnv::seq_step(const std::vector<ActionType>& actions) {
        const std::vector<AbstractAgent*> agent_list = this->getAgents();
        if (actions.size() != agent_list.size()) {
            throw "Action list size doesn't match agent list size";
        }
        _run_recorder.new_run();

        // Step 1: Action -> action_updates
        Logger::Report ("stage 1\n", Logger::INFO);
        std::unordered_map<AbstractAgent*, std::vector<uint32_t>> agent_action_updates;
        _run_recorder.start();
        for (int i = 0; i < agent_list.size(); ++i) {
            const auto& agent = agent_list[i];

            const auto& updates = agent->doAction(actions[i]);

            for (const auto& kv_pair : updates) {
                AbstractAgent* affected_agent = kv_pair.first;
                const std::vector<uint32_t>& action_list = kv_pair.second;
                std::vector<uint32_t>& affected_list = agent_action_updates[affected_agent];
                affected_list.insert(affected_list.end(),
                                     action_list.begin(),
                                     action_list.end());
            }
        }
        _run_recorder.stop();

        // Step 2: Apply per agent action updates
        std::unordered_map<AbstractPosition*, std::vector<AbstractUpdate*>> tag_map_updates;
        _run_recorder.start();
        for (auto& kv_pair : agent_action_updates) {
            AbstractAgent* agent = kv_pair.first;
            std::vector<uint32_t>& action_updates = kv_pair.second;

            const auto map_updates = agent->doActionAgentCollate(action_updates);
            for (const auto& update_pair : map_updates) {
                tag_map_updates[update_pair.first].push_back(update_pair.second);
            }
        }
        _run_recorder.stop();

        // Step 3: Invoke map updates
        _run_recorder.start();
        this->getCurrentMap()->doMapUpdates(tag_map_updates);
        _run_recorder.stop();

        // Step 4: Get agent rewards
        std::vector<uint64_t> agent_rewards(agent_list.size());
        _run_recorder.start();
        for (int i = 0; i < agent_list.size(); ++i) {
            agent_rewards[i] = this->getAgentRewards(agent_list[i]);
        }
        _run_recorder.stop();

        return std::move(agent_rewards);
}

std::vector<uint64_t> AbstractEnv::omp_step(const std::vector<ActionType>& actions) {
        const std::vector<AbstractAgent*> agent_list = this->getAgents();
        if (actions.size() != agent_list.size()) {
            throw "Action list size doesn't match agent list size";
        }
        _run_recorder.new_run();

        // Step 1: Action -> action_updates
        Logger::Report ("stage 1\n", Logger::INFO);
        std::unordered_map<AbstractAgent*, std::vector<uint32_t>> agent_action_updates;
        _run_recorder.start();
        #pragma omp parallel
        {
            std::unordered_map<AbstractAgent*, std::vector<uint32_t>> local_updates;

            #pragma omp for nowait
            // Allow agents to complete this computation and then move
            // on to the critical section
            for (int i = 0; i < agent_list.size(); ++i) {
                const auto& agent = agent_list[i];

                const auto& updates = agent->doAction(actions[i]);
                for (auto it = updates.begin(); it != updates.end(); ++it) {
                    AbstractAgent* affected_agent = it->first;
                    const std::vector<uint32_t>& action_list = it->second;
                    std::vector<uint32_t>& affected_list = local_updates[affected_agent];
                    affected_list.insert(affected_list.end(),
                                         std::make_move_iterator(action_list.begin()),
                                         std::make_move_iterator(action_list.end()));
                }
            }

            #pragma omp critical
            {
                for (auto& local_pair : local_updates) {
                    agent_action_updates[local_pair.first].insert(
                            agent_action_updates[local_pair.first].begin(),
                            std::make_move_iterator(local_pair.second.begin()),
                            std::make_move_iterator(local_pair.second.end()));
                }
            }
        }
        _run_recorder.stop();

        // Step 2: Apply per agent action updates
        std::unordered_map<AbstractPosition*, std::vector<AbstractUpdate*>> tag_map_updates;
        _run_recorder.start();
        #pragma omp parallel
        {
            std::unordered_map<AbstractPosition*, std::vector<AbstractUpdate*>> local_updates;

            // Currently parallelizing over the hash table's buckets
            #pragma omp for nowait
            for (int i = 0; i < agent_action_updates.bucket_count(); ++i) {
                for (auto it = agent_action_updates.begin(i); it != agent_action_updates.end(i); ++it) {
                    AbstractAgent* agent = it->first;
                    std::vector<uint32_t>& action_updates = it->second;

                    const auto map_updates = agent->doActionAgentCollate(action_updates);
                    for (const auto& update_pair : map_updates) {
                        local_updates[update_pair.first].push_back(update_pair.second);
                    }
                }
            }

            #pragma omp critical
            {
                for (const auto& update_pair : local_updates) {
                    tag_map_updates[update_pair.first].insert(
                            tag_map_updates[update_pair.first].begin(),
                            std::make_move_iterator(update_pair.second.begin()),
                            std::make_move_iterator(update_pair.second.end()));
                }
            }
        }
        _run_recorder.stop();

        // Step 3: Invoke map updates
        _run_recorder.start();
        this->getCurrentMap()->doMapUpdates(tag_map_updates);
        _run_recorder.stop();

        // Step 4: Get agent rewards
        std::vector<uint64_t> agent_rewards(agent_list.size());
        _run_recorder.start();
        for (int i = 0; i < agent_list.size(); ++i) {
            agent_rewards[i] = this->getAgentRewards(agent_list[i]);
        }
        _run_recorder.stop();

        return std::move(agent_rewards);
}

void AbstractEnv::dump_data(const std::vector<std::string>& header,
                            const std::string& filename, char mode) {
    _run_recorder.dump_data(header, filename, mode);
}
