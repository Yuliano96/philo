#!/bin/bash

# Verify command-line arguments.
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <number_of_philosophers> <minimum_meals>"
    exit 1
fi

total=$1
min_meals=$2
log_file="philo_log.txt"

# Validate arguments.
if ! [[ "$total" =~ ^[1-9][0-9]*$ && "$min_meals" =~ ^[1-9][0-9]*$ ]]; then
    echo "Error: arguments must be positive integers."
    exit 1
fi

# Check that the log file exists.
if [ ! -f "$log_file" ]; then
    echo "Error: $log_file not found."
    exit 1
fi

failed=0

# Check the number of meals for each philosopher.
for ((i = 1; i <= total; i++)); do
    count=$(grep -c "Philosopher $i is eating$" "$log_file")

    if [ "$count" -lt "$min_meals" ]; then
        echo "❌ Philosopher $i ate $count times (minimum: $min_meals)."
        failed=1
    else
        echo "✅ Philosopher $i ate $count times."
    fi
done

# Check for philosopher deaths.
if grep -q "died" "$log_file"; then
    echo "❌ A philosopher died during the simulation."
    failed=1
fi

# Print the final result.
if [ "$failed" -eq 0 ]; then
    echo "✅ SUCCESS: All philosophers completed the required meals."
else
    echo "❌ FAILURE: The simulation did not pass all checks."
    exit 1
fi

# ============================================================
# HOW TO RUN THE TEST
#
# 1. Compile the project:
#    make
#
# 2. Run the simulation and save the output:
#    ./philo 5 800 200 200 3 | tee philo_log.txt
#
# 3. Verify that each philosopher ate at least 3 times:
#    bash check_meals.sh 5 3
#
# 4. Example with 100 philosophers:
#    ./philo 100 800 200 200 3 > philo_log.txt
#    bash check_meals.sh 100 3
#
# Arguments:
#   $1 = Number of philosophers.
#   $2 = Minimum number of meals per philosopher.
#
# The script reads philo_log.txt and checks:
#   - Whether each philosopher ate enough times.
#   - Whether any philosopher died during the simulation.
# ============================================================
