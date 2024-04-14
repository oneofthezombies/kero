package tree_sitter_kero_test

import (
	"testing"

	tree_sitter "github.com/smacker/go-tree-sitter"
	"github.com/tree-sitter/tree-sitter-kero"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_kero.Language())
	if language == nil {
		t.Errorf("Error loading Kero grammar")
	}
}
