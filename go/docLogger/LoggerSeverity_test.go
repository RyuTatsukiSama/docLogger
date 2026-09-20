package docLogger

import (
	"fmt"
	"testing"
)

func TestSeverity(t *testing.T) {
	var tests = []struct {
		is   int
		want int
		name string
	}{
		{Trace.value, 0, "Trace"},
		{Debug.value, 1, "Debug"},
		{Info.value, 2, "Info"},
		{Warning.value, 3, "Warning"},
		{Error.value, 4, "Error"},
		{Critical.value, 5, "Critical"},
		{None.value, 6, "None"},
	}

	for _, tt := range tests {
		testname := fmt.Sprintf("%s", tt.name)
		t.Run(testname, func(t *testing.T) {
			if tt.is != tt.want {
				t.Errorf("got %d, want %d", tt.is, tt.want)
			}
		})
	}
}
