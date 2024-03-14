// Copyright 2019 The etcd Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package quorum

import (
	"testing"
)

// TestDataDriven parses and executes the test cases in ./testdata/*. An entry
// in such a file specifies the command, which is either of "committed" to check
// CommittedIndex or "vote" to verify a VoteResult. The underlying configuration
// and inputs are specified via the arguments 'cfg' and 'cfgj' (for the majority
// config and, optionally, majority config joint to the first one) and 'idx'
// (for CommittedIndex) and 'votes' (for VoteResult).
//
// Internally, the harness runs some additional checks on each test case for
// which it is known that the result shouldn't change. For example,
// interchanging the majority configurations of a joint quorum must not
// influence the result; if it does, this is noted in the test's output.
func TestDataDriven(t *testing.T) {
	goTestDataDriven(t)
}
