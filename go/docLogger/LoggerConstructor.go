package docLogger

import "context"

func NewLogger(threadName string, options LoggerOptions, iCtx context.Context) (l *Logger, oCtx context.Context, err error) {
	l = &Logger{}

	if iCtx != nil {
		if ctxThreadName, ok := iCtx.Value("threadName").(string); ok {
			l.threadName = ctxThreadName
		} else {

		}

	} else {

	}

	return l, oCtx, err
}
