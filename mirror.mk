#!/usr/bin/make -f

push: fetch-official
	git push --force origin refs/remotes/official/branches/default/tip:master

fetch-official: git-cinnabar
	(git remote | grep -q official) || git remote add official hg::http://hg.code.sf.net/p/scintilla/code
	git fetch official branches/default/tip:refs/remotes/official/branches/default/tip

.PHONY: push fetch-official

fetch-official: export PATH := $(abspath git-cinnabar):$(PATH)

git-cinnabar.linux.x86_64.tar.xz:
	wget https://github.com/glandium/git-cinnabar/releases/download/0.5.11/git-cinnabar.linux.x86_64.tar.xz -O $@

git-cinnabar: git-cinnabar.linux.x86_64.tar.xz
	tar xf $<
	touch $@
