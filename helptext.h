#define HELP_TEXT \
"ecode v0.0.0\n\nDESCRIPTION:\n    Very simple program that outputs the name " \
"of the error associated with an\n    error code and its description. Vice-ve" \
"rsa, the name of the error code can\n    be used to fetch its error code and" \
" description.\n\nEXAMPLES:\n    $ ecode 12\n    12 ENOMEM Out of memory\n\n " \
"   $ ecode EFAULT\n    14 EFAULT Bad address\n\nUSAGE:\n    ecode [--help] <" \
"code|name>\n\nARGUMENTS:\n    code        The error code numerical value to " \
"lookup.\n    name        The error code string name to lookup.\n"
