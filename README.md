This project uses Mentalab code

# To run the project with the files recorded
# Change the file name after -f parameter
python -m egg2lamp -n Explore_DAAQ -fn 50.0 -fbp 3.0 40.0 --simulate_lamp -f Files/try_004_ExG.bdf --loop

# To run the project while using the EEG
python -m egg2lamp -n Explore_DAAQ -fn 50.0 -fbp 3.0 40.0 -p COM9 --simulate-lamp
