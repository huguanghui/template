#!/usr/bin/env bash

# Init option {{{
Color_off='\033[0m'       # Text Reset

# terminal color template {{{
# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White

# Underline
UBlack='\033[4;30m'       # Black
URed='\033[4;31m'         # Red
UGreen='\033[4;32m'       # Green
UYellow='\033[4;33m'      # Yellow
UBlue='\033[4;34m'        # Blue
UPurple='\033[4;35m'      # Purple
UCyan='\033[4;36m'        # Cyan
UWhite='\033[4;37m'       # White

# Background
On_Black='\033[40m'       # Black
On_Red='\033[41m'         # Red
On_Green='\033[42m'       # Green
On_Yellow='\033[43m'      # Yellow
On_Blue='\033[44m'        # Blue
On_Purple='\033[45m'      # Purple
On_Cyan='\033[46m'        # Cyan
On_White='\033[47m'       # White

# High Intensity
IBlack='\033[0;90m'       # Black
IRed='\033[0;91m'         # Red
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
IBlue='\033[0;94m'        # Blue
IPurple='\033[0;95m'      # Purple
ICyan='\033[0;96m'        # Cyan
IWhite='\033[0;97m'       # White

# Bold High Intensity
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
BIPurple='\033[1;95m'     # Purple
BICyan='\033[1;96m'       # Cyan
BIWhite='\033[1;97m'      # White

# High Intensity backgrounds
On_IBlack='\033[0;100m'   # Black
On_IRed='\033[0;101m'     # Red
On_IGreen='\033[0;102m'   # Green
On_IYellow='\033[0;103m'  # Yellow
On_IBlue='\033[0;104m'    # Blue
On_IPurple='\033[0;105m'  # Purple
On_ICyan='\033[0;106m'    # Cyan
On_IWhite='\033[0;107m'   # White
# }}}
#
# version
Version='1.8.0-dev'
#System name
System="$(uname -s)"

# }}}

# need_cmd {{{
need_cmd () {
  if ! hash "$1" &>/dev/null; then
    error "需要 '$1' （找不到命令）"
    exit 1
  fi
}
# }}}

# success/info/error/warn {{{
msg() {
  printf '%b\n' "$1" >&2
}

success() {
  msg "${Green}[✔]${Color_off} ${1}${2}"
}

info() {
  msg "${Blue}[➭]${Color_off} ${1}${2}"
}

error() {
  msg "${Red}[✘]${Color_off} ${1}${2}"
  exit 1
}

warn () {
  msg "${Yellow}[⚠]${Color_off} ${1}${2}"
}
# }}}

# echo_with_color {{{
echo_with_color () {
  printf '%b\n' "$1$2$Color_off" >&2
}
# }}}

# welcome {{{


welcome () {
    echo_with_color ${Yellow} "linux develope environment install ..."
}

# }}}

# rsync -avz -e "ssh -p 5022" /usr/local/bin/clash hgh@1.13.20.3:/volume1/homes/hgh/software/linux/clash
# rsync -avz -e "ssh -p 5022" hgh@1.13.20.3:/volume1/homes/hgh/software/linux/clash .
# rsync -avz -e "ssh -p 5022" hgh@1.13.20.3:/volume1/homes/hgh/software/linux/frp .

### main {{{
main () {
  welcome
  sudo apt-get install -y build-essential git zsh autojump silversearcher-ag fd-find openssl libssl-dev pkg-config cmake automake autoconf libtool libevent-dev openssh-server yadm curl net-tools tmux
  git config --global user.name "hugh"
  git config --global user.email "huguanghui1971@gmail.com"
  # chsh -s "$(which zsh)"
  # sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
  # git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ~/.oh-my-zsh/themes/powerlevel10k
  # git clone https://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions
  # curl -O https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
  # chmod a+x Miniconda3-latest-Linux-x86_64.sh
  # ./Miniconda3-latest-Linux-x86_64.sh
  # conda init zsh
}

# }}}

main "$@"

