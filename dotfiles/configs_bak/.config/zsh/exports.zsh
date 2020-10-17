# Uncomment the following line to use case-sensitive completion.
CASE_SENSITIVE="true"

#ZSH_THEME="ys"

zle_highlight=('paste:none')

# Which plugins would you like to load?
plugins=(
  git
  zsh-syntax-highlighting
  zsh-autosuggestions
)
export ZSH="$HOME/.oh-my-zsh"
source $ZSH/oh-my-zsh.sh

source /usr/share/autojump/autojump.zsh

# export
export TF_FORCE_GPU_ALLOW_GROWTH=true
# Preferred editor for local and remote sessions
 if [[ -n $SSH_CONNECTION ]]; then
   export EDITOR='nvim'
 else
   export EDITOR='nvim'
 fi
#autoload -U colors && colors
export CLICOLOR=1
export FZF_DEFAULT_COMMAND='rg --files --hidden'
export FZF_DEFAULT_OPTS='--height 40% --reverse --border'
#export FZF_CTRL_T_COMMAND="$FZF_DEFAULT_COMMAND"
export FZF_ALT_C_COMMAND="$FZF_DEFAULT_COMMAND"
export MANPATH="/usr/local/man:$MANPATH"
export MANPAGER='nvim +Man!'
export MANWIDTH=999
