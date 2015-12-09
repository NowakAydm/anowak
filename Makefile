
all : copy push

copy :
	@cp -fv ~/projects/STUFF/.emacs ~
	@cp -fv ~/projects/STUFF/.zshrc ~

new :
	sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

push :
	@git status -s
	@git add -A
	@git add -u
	@git commit -m "$USER - `date`"
	@git push