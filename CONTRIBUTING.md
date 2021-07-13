# How to make your first contributing as a beginner?
This is the main problem with all beginners that how can they make their first contributing. So in this documentation I will let you know that how can you contribute to [HMT](https://github.com/UG-SEP/HMT) project
even every project contributing.md guidelines are nearby same.

Tip: **As a beginner you should use Git Bash to get familiar with it.**

## Using Git Bash 
Install [Git Bash](https://git-scm.com/downloads)

So let start the steps to make your first contribution

### Clone the Repository
To clone the repository go to your forked repository and click on code button on the top right side `Code` and copy the https `URL`
```
$ git clone https://github.com/<your username>/HMT.git
```
![git clone](https://github.com/UG-SEP/HMT/blob/main/Images/git%20clone.jpg)

replace <your username> to your username i.e. `UG-SEP` like this after doing it
you may see something like this 
`git clone https://github.com/UG-SEP/HMT.git`
  
## Create a Branch
Change the directory to the clone repository
```
  cd HMT
```
Now create a branch by using `git branch`command
  ```
  $ git branch <your branch name>
  ```
  ![git branch](https://github.com/UG-SEP/HMT/blob/main/Images/git%20branch.jpg)
  
  replace <your branch name> to whatever you wanted to name the branch i.e. `Patch-1`
  Now checkout to the branch by using `git checkout` command
  ```
  $ git checkout <branch name>
  ```
  ![git checkout](https://github.com/UG-SEP/HMT/blob/main/Images/git%20checkout.jpg)
  
  replace <branch name> to the name you have given to the branch i.e.: `Patch-1`
  
  ### Make necessary changes and commit those changes
  Now add the necssary file by using any editor like `VS Code` and then save the changes
  Now check whether the changes done in the repository or not by typing 
  `git status` in git bash
  Now add the changes by using `git add` commmand
  You can add all the files in a repository to the staging area using the git add -A command or the git add . command.
  ```
  $ git add -A
  ```  
or
  
You can also use the git add . command. This command adds all the files in the folder you are presently viewing to the staging area.
  ```
  $ git add .
  ```
  ![Git add](https://github.com/UG-SEP/HMT/blob/main/Images/git%20add%20.jpg)
  
### Commit changes
  To commit change write `git commit` command
  ```
  $ git commit -m "add here a appropriate message"
  ```
  ![git commit](https://github.com/UG-SEP/HMT/blob/main/Images/git%20commit%20.jpg)
  
  ### Push the changes
  After making commit now it time to push the changes done in the forked repository
  ```
  $ git push origin <your branch name>
  ```
  ![git push](https://github.com/UG-SEP/HMT/blob/main/Images/git%20push.jpg)
  
  replace <your branch name> to the branch you have created before i.e: `Patch-1`
  
  ### Create a Pull request
  
  To create a pull request first of all click on the `Compare and Pull Request`
  ![Compare and Pull Request](https://github.com/UG-SEP/HMT/blob/main/Images/git%20compare%20and%20pull.jpg)
  
  After that write the Title of the Commit and a proper description about the changes and then click on `Pull Request`
  
  ![Pull request](https://github.com/UG-SEP/HMT/blob/main/Images/pull%20request.jpg)
  
  ### Congrats your have make your first contribution 🎉🎉
  
  
  
