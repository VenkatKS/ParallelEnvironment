#!/bin/env python3
import logging
import sys

# Modify this variable to change the log level
LOG_LEVEL = logging.DEBUG
FORMAT = "%(levelname)s [%(asctime)s] [%(filename)s:%(funcName)s:%(lineno)d] %(message)s"
TIME_FORMAT = "%H:%M:%S"

# Setting up a logger for the package which writes to stderr
Log = logging.getLogger(__name__)
Log.setLevel(LOG_LEVEL)
ch = logging.StreamHandler(sys.stderr)
formatter = logging.Formatter(FORMAT, datefmt=TIME_FORMAT)
ch.setFormatter(formatter)
Log.addHandler(ch)

Log.info("Initialied logger")
