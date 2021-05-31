#!/usr/bin/make -f

push: fetch-upstream
	git push --force origin refs/remotes/upstream/branches/default/tip:master

fetch-upstream: git-cinnabar
	(git remote | grep -q upstream) || git remote add upstream hg::http://hg.code.sf.net/p/scintilla/code
	git fetch upstream branches/default/tip:refs/remotes/upstream/branches/default/tip

.PHONY: push fetch-upstream

fetch-upstream: export PATH := $(abspath git-cinnabar):$(PATH)

git-cinnabar.linux.x86_64.tar.xz:
	wget https://github.com/glandium/git-cinnabar/releases/download/0.5.7/git-cinnabar.linux.x86_64.tar.xz -O $@

git-cinnabar: git-cinnabar.linux.x86_64.tar.xz
	tar xf $<
	touch $@
