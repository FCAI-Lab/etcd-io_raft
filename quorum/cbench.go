package quorum

import (
	"testing"
)

/*
#cgo LDFLAGS: -L./quorumC -lbench_test
#include "quorumC/bench_test.h"
#cgo LDFLAGS: -L./quorumC -lvector
#include "quorumC/vector.h"
*/
import "C"

func goBenchmarkMajorityConfig_CommittedIndex(b *testing.B, n int) {
	C.cBenchmarkMajorityConfig_CommittedIndex(C.int(b.N), C.int(n))
}
