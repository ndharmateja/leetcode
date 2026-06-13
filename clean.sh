find . -type f \( -name "*.class" \) -exec rm -f {} +
find . -type f -name "main" -exec rm -f {} +
find . -type d -name "main.dSYM" -exec rm -rf {} +