#!/bin/bash

# cd into sdk root dir
# run cmd:
# rm -rf ~/diff_workspace/; repo forall -c bash ~/git_gen_diff_dir_workspace.sh
# cp changed_files in ~/diff_worksapce/ into this project to log diff

targetfolder=~/diff_workspace

gitdirpath=`git rev-parse --show-toplevel`
gitdirname=`basename $gitdirpath`
commit_hash=$(git rev-parse --short HEAD)
commit_hash_full=$(git rev-parse HEAD)
# 获取仓库远程URL
repo_url=$(git remote get-url origin 2>/dev/null || echo "No remote origin configured")
# 获取当前分支名称
branch_name=$(git branch --show-current 2>/dev/null || echo "Detached HEAD")
targetgitfolder=$targetfolder/${gitdirname}_${commit_hash}

# echo "--- target folder is $targetfolder"
# echo "--- dirname is $gitdirname"
# echo "--- dirpath is $targetgitfolder"

rm -rf $targetgitfolder

# echo "get diff changed_files..."
changed_files_git=`git diff --name-only HEAD`
new_files_git=`git ls-files --others --exclude-standard`

# printf interprets \abc excapes
changed_files=`printf "%b" "$changed_files_git"`
new_files=`printf "%b" "$new_files_git"`

# "abc" into array 
# avoid not find "123", while file is 123
eval files_arr=($changed_files)
changed_files=("${files_arr[@]}")

printf "changed\n"
printf "=> %s\n" "${changed_files[@]}"

eval files_arr=($new_files)
new_files=("${files_arr[@]}")
printf "new\n"
printf "=> %s\n" "${new_files[@]}"

# exit

echo "`pwd`"

if [ -z "$changed_files" ] && [ -z "$new_files" ]
	then
	echo "no changes or new"
	echo ""
	exit 0
	fi

	echo "--> $targetgitfolder"

	mkdir -p $targetgitfolder

# 创建README文件
cat > $targetgitfolder/README.md << EOF
# 差异比较信息

## 仓库信息
- **仓库名称**: $gitdirname
- **远程地址**: $repo_url
- **当前分支**: $branch_name
- **Commit Hash (短)**: $commit_hash
- **Commit Hash (完整)**: $commit_hash_full
- **生成时间**: $(date)

## 文件说明
- \`old/\`: 原始文件（来自HEAD commit）
- \`new/\`: 修改后的文件（包含未暂存的更改）
- \`git.diff\`: 完整的git diff输出

## 生成命令
此目录由脚本 \`git_gen_diff_dir_workspace.sh\` 自动生成
EOF

# echo "creating git diff..."
git diff HEAD > $targetgitfolder/git.diff

# echo "archive new..."
# changed_files could be removed
tar --ignore-failed-read --warning=no-failed-read -cf $targetgitfolder/new.tar "${changed_files[@]}" "${new_files[@]}"

# echo "archive old..."
git archive -o $targetgitfolder/old.tar HEAD "${changed_files[@]}"

cd $targetgitfolder
rm new -rf
rm old -rf
mkdir -p new old
tar -xf new.tar -C new
tar -xf old.tar -C old
rm new.tar old.tar 

echo ""

sleep 1
