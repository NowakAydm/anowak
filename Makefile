
all : copy push

copy :
	@cp -fv ./STUFF/.emacs ~
	@cp -fv ./STUFF/.zshrc ~
	@mkdir -p ~/.emacs.d/lisp
	@cp -fv ./STUFF/emacs/highlight-chars.el ~/.emacs.d/lisp/
	@cp -fv ./STUFF/emacs/template.el ~/.emacs.d/lisp/
	@mkdir -p ~/.templates
	@cp -fv ./STUFF/.templates/* ~/.templates

new :
	sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

push :
	@git status -s
	@git add -A
	@git add -u
	@git commit -m "$USER - `date`"
	@git push
