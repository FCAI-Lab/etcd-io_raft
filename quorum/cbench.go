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
	// c := MajorityConfig{}
	// l := mapAckIndexer{}

	C.cBenchmarkMajorityConfig_CommittedIndex(C.int(b.N), C.int(n))

	// for i := uint64(0); i < uint64(n); i++ {
	// 	c[uint64(C.majorityConfigId(C.uint64_t(i)))] = struct{}{}
	// 	l[uint64(C.mapAckIndexerId(C.uint64_t(i)))] = Index(C.mapAckIndexerIdx(C.uint64_t(i)))
	// }

	// C.majorityConfigmapAckIndexerFree()

	// for i := 0; i < b.N; i++ {
	// 	_ = c.bench_testCommittedIndex(l)
	// }
}
