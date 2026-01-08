package docLogger

import (
	"context"
	"os"
)

func NewLogger(threadName string, options LoggerOptions, iCtx context.Context) (l *Logger, oCtx context.Context, err error) {
	l = &Logger{}
	l.lOpts = options
	l.timeProvider = l.lOpts.timeProvider

	if iCtx != nil {
		if ctxThreadName, ok := iCtx.Value("threadName").(string); ok {
			l.threadName = ctxThreadName
		} else {
			oCtx = context.WithValue(iCtx, "threadName", threadName)
			l.threadName = threadName
		}
	} else {
		oCtx = context.WithValue(context.Background(), "threadName", threadName)
		l.threadName = threadName
	}

	if l.lOpts.IsOutputConsole() {
		l.RegisterOutputStream(os.Stdout)
	}

	if l.lOpts.IsOutputFile() {
		if l.lOpts.GetFileStream() != nil {
			l.RegisterOutputStream(l.lOpts.GetFileStream())
		}
	}

	return l, oCtx, err
}
