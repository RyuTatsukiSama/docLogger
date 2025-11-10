package docLogger

import (
	"io"
	"sync"
	"time"
)

var (
	lock       sync.Mutex
	threadName string
)

type Logger struct {
	severityThreshold LoggerSeverity // Trace by default

	outputStreams []io.Writer

	logCallbacks []func(string)

	timeProvider func() time.Time

	lOpts LoggerOptions

	thradName string
}
