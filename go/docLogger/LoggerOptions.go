package docLogger

import (
	"io"
	"time"
)

type LoggerOptions struct {
	isOutputConsole bool
	isOutputFile    bool
	fileName        string
	fileStream      *io.Writer
	timeProvider    func() time.Time
}
