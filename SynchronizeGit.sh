cp -v ~/projects/STUFF/.emacs ~
cp -v ~/projects/STUFF/.zshrc ~

git status
git add -A
git add -u
git commit -m "$USER - `date`"
git push