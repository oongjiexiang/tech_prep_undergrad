1. Configuring Git
```
git config --list --show-origin [user.name/user.email/init.defaultBranch]
git config --global/local/system core.editor emacs
```
- Without specifying `global` or `system`, the default configuration occurs at the `local` (that repo) level. It is stored in .git/config of the repo
- At the `global` (that user's) level, the config is stored in ~/.config/git/config or ~/.gitconfig
- At the `system` level, the config is stored in [path of git]/etc/gitconfig

2. 
```
git init
git clone [url] [alternative_directory_name]
```

3. `git status [-s or --short]`
First letter: status in staging area
Second letter: status in working directory
eg. 
- MM: staged after modifiation, but modified again and not staged
- M : staged after modification
- A : staged without modification
-  M: not staged, but modified

4.  .gitignore
- `**`: nested directories

5. Compare staged and unstaged files' details
```
git diff # difference between staged and unstaged files
git diff --cached OR --staged # difference between staged and last commit files
```

6. Commit
```
git commit -a -m "message" # skips `git add`
```

7. Remove
```
git rm files    # untrack it and delete it
git rm --cached files # unstage it
```

8. Rename
```
git mv file1 renamed_file
# similar as 
mv file1 renamed_file
git rm file1
git add renamed_file
```

9. Commit History
```
git log
git log [-p or --patch] [-3]
git log [--stat or --shortstat] #--stat shows the filenames as well besides number of insertions etc
git log --pretty=oneline OR git log --oneline
git log --pretty=[short, full, fuller] # short has only author, full has committer, fuller has their dates
git log --pretty=format:"%h %T - %an (%ad) | %ce (%cr) | %s" # abbreviated hash, full tree has, author name, his date, commiter email, committer relative date, subject
git log --graph (shows branches) --name-only --name-status --abbrev-commit (short hash)
git log --since=2.weeks
git log --after="2020-10-20"
git log -S string_to_match_normally_function_name -- path_to_file_only_state_at_end
git log --author="author" --committer "not_exact_match" --grep="regex" --no-merges
``` 
10. Undo
```
git restore --staged filename # unstage a staged file
git restore filename # restore to its previous commit. WILL LOSE THE EDIT
git commit --amend # to make minor improvements but replace the last commit. Good to avoid cluttering
```

11. Remotes
```
git remote         # show the remote handles or servers I have 
git remote -v      # also shows the URL
git remote add shortName www.url.com
git fetch remoteHandle            # update the data from the remote, but no merging yet
git pull [remote]           # merges after fetching
git push remoteHandle branch
git remote show origin            # see infor about a particular remote
git remote rename remoteHandle newRemoteHandle
git remote rm remoteHandle
```

12. Tagging
```
git tag               # show tags
git tag [-l, --list] "regex"
git tag v1.0           # lightweight tags, only a pointer to the commit
git tag -a v2.0 -m "message comes if annotated tag"       # annotated tags are stored as full objects in the Git DB
git tag -a v3.0 9fcb13        # to tag PAST commit
git tag -d v2.0
git show v1.0
git push origin --tags      # push all tags
git push origin v1.0
git push origin :/refs/tags/v1.0    # push null to the tag remotely
git push origin --delete v1.0
git checkout v1.0     # enters detached HEAD state. Committed changes will be LOST
git switch -c newBranchToSaveChanges       # after changing, but before committing
git checkout -b newBranchToSave v1.0         # duplicate the branch after commit
```

13. Stashing
```
git stash                            # stash the current work. It keeps all TRACKED files and save them to a STACK
git stash list                       # list all the stashes                                        
git stash apply [stash@{n}] --index  # apply the stash on ANY branch; apply the index (which files are staged, not staged)
git stash drop stash@{n}             # drop that stash. `apply` doesn't drop it  
git stash pop                        # combines `apply` and `drop`
git stash --keep-index               # stash the changes with info about which files are staged or not staged
git stash [--include-untracked, -u]  # include all untracked files, e.g. *.class files
git stash [--all,-a]                 # include even files in .gitignore
git stash --patch                    # manually see which changes I want to stash
git stash branch newBranchToContinue # create a new branch to apply the stash. Helps to avoid merge conflicts if accidentally continue work without reapplying stash
git clean -d [-n,-i]                 # clean the DIR (better than `git restore`). include subdir, --dry-run, --interactive so that I know which files will be deleted
git clean -f -x                      # delete forcefully, delete even files in .gitignore. `-f` works if clean.requireForce=True
git clean -ffd                       # double force XD if the repo is cloned or copied
```

14. Merging
```
# Merging SOP
git merge hotfix                    # take hotfix INTO currentBranch; NOT YET DELETE
git branch -d hotfix 
```
> Merging types

| Merging type | condition | Git Logic |
| --- | --- | --- |
| fast-forward | when a is common ancestor of to_merge_into | move master pointer forward |
| recursive | when a is not ancestor of b | a, b, common ancestor commits form a new commit |
| merge conflict | merging has NOT OCCURED | `git status` shows conflicting files, need `git add` to mark files after resolving and `git commit` |

15. Branch Management
```
git merge -v                # see last commits too
git branch --merged         # can delete those branches without *
git branch --no-merged      # cannot delete those branches unless git branch -D theBranch
```

16. Remote branches
```
# Rename remote branch?
git branch --move bad_branch good_branch
git push --set-upstream origin good_branch      # actually is delete and replace
git push origin --delete bad_branch

# check remote references
git ls-remote <remote>              # shows branches and tags
git remote show <remote>            # shows branches only

# Remote-tracking branch on local machine tracks the state of remote branches
# A read-only bookmark. If other devs modify server repo, this branch stays at the original commit
git fetch [remote]      # update the remote-tracking branch, NOT THE local branch!
git clone -o name2
git remote add name3 <httplink>

# Merging SOP via git fetch = just git pull
git fetch
git merge <serverfix>

# copy to a tracking branch via git fetch
git fetch
git checkout -b serverfix origin/serverfix

# Track branches
git fetch -all
git branch -vv

# push to different branch name
git push origin localBranch remoteBranch
git config --global credential-helper cache         # to save password
```

17. Rebasing
- **never rebase commits outside my repository or where people work on**
- Used to rebase local changes before pushing to clean up work when too many branches are created, and we want others to see as if we just did work from the main branch
```
# SOP when client branches from server, which then branches from master
git rebase --onto master server client          # take the point where client branches from server, rebase onto master
git checkout master                         # rebase only deletes the client branch and mirrors it as the result of extending from master, but still need to merge
git merge client

# Typical SOP
git rebase basebranch topicbranch
git checkout basebranch
git merge topicbranch
git branch -d topicbranch

# If rebase on remote branches?
git pull --rebase               # If not it will be very problematic
```

18. Git SSH (only two steps)
- `ssh-keygen` on terminal
- Copy the whole content from id_rsa.**pub** into my GitHub