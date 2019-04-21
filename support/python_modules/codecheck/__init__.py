#!/usr/bin/python3
from obi.util.logging_helper import create_logger
from obi.util.logging_helper import add_obi_formatter
from obi.util.logging_helper import add_obi_formatter_short
logger = create_logger("check_modify_code")

for handler in logger.handlers:
    add_obi_formatter_short(handler)