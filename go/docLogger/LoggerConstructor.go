package docLogger

import (
	"os"
)

func NewLogger(threadName string, options LoggerOptions) (l *Logger) {
	l = &Logger{}
	l.lOpts = options
	l.timeProvider = l.lOpts.timeProvider

	l.threadName = threadName

	if l.lOpts.IsOutputConsole() {
		l.RegisterOutputStream(os.Stdout)
	}

	if l.lOpts.IsOutputFile() {
		if l.lOpts.GetFileStream() != nil {
			l.RegisterOutputStream(l.lOpts.GetFileStream())
		}
	}

	return l
}

func NewLoggerWithGOpts(threadName string) (l *Logger) {
	return NewLogger(threadName, *gOpts)
}
