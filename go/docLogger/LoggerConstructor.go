package docLogger

import "context"

func NewLogger(threadName string, options LoggerOptions, iCtx context.Context) (l *Logger, oCtx context.Context, err error) {
	l = &Logger{}
	l.lOpts = options

	if iCtx != nil {
		if ctxThreadName, ok := iCtx.Value("threadName").(string); ok {
			l.threadName = ctxThreadName
		} else {

		}

	} else {

	}

	if l.lOpts.outputConsole {

	}

	if l.lOpts.outputFile {

	}

	return l, oCtx, err
}
