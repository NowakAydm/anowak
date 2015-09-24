PATH=$HOME/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/usr/texbin
HISTFILE=~/.zshrc_history
SAVEHIST=1000
HISTSIZE=1000

setopt inc_append_history
setopt share_history

if [[ -f ~/.myzshrc ]]; then
  source ~/.myzshrc
fi

ZSH_THEME="robbyrussell"
USER=`/usr/bin/whoami`
export USER
GROUP=`/usr/bin/id -gn $user`
export GROUP
MAIL="$USER@student.42.fr"
export MAIL

alias l="ls -laGh"
alias e="emacs"
alias r="rm -v *~ ; rm -v .*~"
alias synchronize="~/projects/SynchronizeGit.sh"