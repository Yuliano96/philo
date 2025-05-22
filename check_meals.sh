#!/bin/bash

# Cambia esto al nombre real de tu archivo
log_file="philo_log.txt"

# Número total de filósofos y mínimo de comidas
total=30
min_comidas=3

for ((i = 1; i <= total; i++)); do
    count=$(grep "Philosopher $i is eating" "$log_file" | wc -l)
    if [ "$count" -lt "$min_comidas" ]; then
        echo "❌ El filósofo $i solo comió $count veces."
    else
        echo "✅ El filósofo $i comió $count veces."
    fi
done


# ./philo 30 500 200 200 3 | tee philo_log.txt

# valgrind --tool=memcheck --leak-check=full --track-origins=yes --log-file=valgrind.log ./philo 12 800 200 200 3