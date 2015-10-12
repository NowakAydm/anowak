all : copy push

copy :
	cp ~/projects/STUFF/.emacs ~
	cp ~/projects/STUFF/.zshrc ~

push :
	@git status -s
	@git add -A
	@git add -u
	@git commit -m "$USER - `date`"
	@git push