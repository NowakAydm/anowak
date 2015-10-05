cp -v ~/projects/.emacs .. ; cp -v ~/projects/.zshrc ..

git status
git add -A
git add -u
git commit -m "$USER - `date`"
git push