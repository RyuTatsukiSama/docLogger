package docLogger

import (
	"fmt"
	"io"
	"time"
)

func (this *Logger) formatLog(severity LoggerSeverity, message string) string {
	return fmt.Sprintf("[%s] [%s] [\033[30;47m%s\033[0m] %s\n", severityText[severity], this.timeProvider().Format("1970-30-12 00:00:00"), this.threadName, message)
}

func (this *Logger) Log(severity LoggerSeverity, message string) {
	if severity.value < this.severityThreshold.value {
		return
	}

	lock.Lock()
	defer lock.Unlock()

	formatedMessage := this.formatLog(severity, message)

	for _, stream := range this.outputStreams {
		stream.Write([]byte(formatedMessage))
	}

	for _, callback := range this.logCallbacks {
		callback(formatedMessage)
	}
}

func (this *Logger) RegisterOutputStream(stream io.Writer) {
	this.outputStreams = append(this.outputStreams, stream)
}

func (this *Logger) RegisterLogCallback(callback func(string)) {
	this.logCallbacks = append(this.logCallbacks, callback)
}

func (this *Logger) Caller() {

}

func (this *Logger) SetSeverityThreashold(threshold LoggerSeverity) {
	this.severityThreshold = threshold
}

// temp function waiting for builder
func (this *Logger) RegisterTimeProvider(timeProvider func() time.Time) {
	this.timeProvider = timeProvider
}
