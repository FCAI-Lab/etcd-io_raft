package quorum

import (
	"testing"
)

/*
#cgo LDFLAGS: -LmajorityC -ldatadriven_test
#include "majorityC/datadriven_test.h"
#cgo LDFLAGS: -LmajorityC -lvector
#include "majorityC/vector.h"
*/
import "C"

func goTestDataDriven(t *testing.T) {
	C.cTestDataDriven()
}
