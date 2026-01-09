package docLogger

func (this *Logger) Trace(message string) {
	this.Log(Trace, message)
}

func (this *Logger) Debug(message string) {
	this.Log(Debug, message)
}

func (this *Logger) Info(message string) {
	this.Log(Info, message)
}

func (this *Logger) Warning(message string) {
	this.Log(Warning, message)
}

func (this *Logger) Error(message string) {
	this.Log(Error, message)
}

func (this *Logger) Critical(message string) {
	this.Log(Critical, message)
}
