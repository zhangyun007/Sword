git config --global user.name "fly3ds"
git config --global user.email "fly3ds@qq.com"

ssh-keygen -t rsa -C "fly3ds@qq.com"
ssh-agent bash
ssh-add id_rsa
ssh -T git@github.com
#ssh -T -p 443 git@ssh.github.com

#git remote add master git@github.com:fly3ds/linux_test.git
git remote add master https://github.com/fly3ds/Shield.git

git push -u master master
