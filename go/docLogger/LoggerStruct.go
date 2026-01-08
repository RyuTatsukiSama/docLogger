package docLogger

import (
	"io"
	"sync"
	"time"
)

var (
	lock sync.Mutex

	severityText map[LoggerSeverity]string = map[LoggerSeverity]string{
		Trace:    "\033[45mTRACE\033[0m",
		Debug:    "\033[44mDEBUG\033[0m",
		Info:     "\033[42mINFO\033[0m",
		Warning:  "\033[43mWARNING\033[0m",
		Error:    "\033[41mERROR\033[0m",
		Critical: "\033[31;47mCRITICAL\033[0m",
	}
)

type Logger struct {
	severityThreshold LoggerSeverity // Trace by default

	outputStreams []io.Writer

	logCallbacks []func(string)

	timeProvider func() time.Time

	lOpts LoggerOptions

	threadName string
}
