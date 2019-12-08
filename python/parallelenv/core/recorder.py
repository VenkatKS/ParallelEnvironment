#!/usr/bin/env python3
from config import Log

import time
from collections import defaultdict

class Recorder:
    """Record wall-clock duration corresponding to tags across multiple runs.

    Uses time.time to measure wall-clock time.
    """
    DefaultTime = -1

    def __init__(self):
        self.__tag_to_time = defaultdict(lambda: Recorder.DefaultTime)
        self.__tag_durations = defaultdict(list)

    def record(self, tag):
        cur_time = time.time()
        if self.__tag_to_time[tag] < 0:
            self.__tag_to_time[tag] = cur_time
        else:
            duration = cur_time - self.__tag_to_time[tag]
            self.__tag_to_time[tag] = Recorder.DefaultTime
            self.__tag_durations[tag].append(duration)

    def get_tag_durations(self):
        return self.__tag_durations

    def dump_csv_by_tag(self, filename, mode='w'):
        """Dumps collected data as a csv. Only writes completed durations."""
        with open(filename, mode) as f:
            for tag, durations in self.__tag_durations.items():
                serialized = "%s,%s\n" % (tag, ','.join([str(round(1000*x, 3)) for x in durations]))
                f.write(serialized)

    def dump_csv_by_run(self, filename, mode='w'):
        with open(filename, mode) as f:
            if mode[0] == 'w':
                cols = ','.join([str(x) for x in self.__tag_durations.keys()])
                f.write(cols + "\n")
            for run in map(list, zip(*self.__tag_durations.values())):
                serialized = ','.join([str(round(1000*x, 3)) for x in run])
                f.write (serialized + "\n")
