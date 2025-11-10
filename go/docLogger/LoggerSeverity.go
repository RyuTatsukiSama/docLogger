package docLogger

type LoggerSeverity struct {
	value int
}

var (
	Trace    = LoggerSeverity{value: 0}
	Debug    = LoggerSeverity{value: 1}
	Info     = LoggerSeverity{value: 2}
	Warning  = LoggerSeverity{value: 3}
	Error    = LoggerSeverity{value: 4}
	Critical = LoggerSeverity{value: 5}
	None     = LoggerSeverity{value: 6}
)
