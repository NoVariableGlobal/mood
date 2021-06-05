# Set up the submodule so dependencies are properly included in the project:
git submodule update --init --recursive

# Define the hooks patch as $root/hooks over $root/.git/hooks so we can run our own hooks:
git config core.hooksPath hooks
