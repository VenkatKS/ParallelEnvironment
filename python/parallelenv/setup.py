from distutils.core import setup
from Cython.Distutils import build_ext
from Cython.Build import cythonize

ext_modules = cythonize(["core/*.py", "gridworld/*.py", "*.py"],
                        language="c++",
                        annotate=True,
                        language_level="3",
                       )
setup(
    name = 'ParallelEnvironment',
    ext_modules = ext_modules,
    cmdclass = {'build_ext': build_ext},
)
