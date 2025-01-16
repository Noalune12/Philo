Youtube : https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&feature=shared

# Problem :
- Several philos around a table with 3 actions : sleep, eat, think
- Fixed number of fork : one per philo but each of them need 2 to eat
- Goal : no philo must die of starvation

# Args :
- Nb of philos
- Time to die
- Time to eat
- Time to sleep
- Nb of time each philo must eat before the simiulation ends (option)

# Structure
- Threads for each philo
- Mutex for forks
- Think, Eat (2 forks), Sleep (after eating)
Handle die of starvation

# Data structure
- Philo's table (list or table): id, status, time since last activity...
- Forks' table (mutex table to protect access to forks)

# Threads management
- Infinite loop with 3 states (think, eat, sleep)

# Sync with mutex
- Mutex for forks
- Mutex global for death (one death not 2 simultanously)

# Showing events
- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died

# Steps
- Init structures + mutex for forks andd global management
- Create a thread for each philo
- In each thread, alternate between think, eat, sleep
- Handle death
- Update state of each philo after each event
