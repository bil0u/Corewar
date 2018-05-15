# Corewar
 "Corewar is a very special programming game created by D. G. Jones and A. K. Dewdney in 1984."
 "It consists in gathering around a virtual machine one to four players."
This players will load champions who will fight with processes, in order, among other things, to make sure that they are told they are alive.  

Processes run sequentially within the same virtual machine, and from the same memory space.  
They can, for example, write to each other in order to corrupt others processes, force others to execute instructions that hurt them, try to recreate on the fly the equivalent software of a Côtes du Rhône 1982, etc ...  

The game ends when no more processes are alive. At this point, the winner is the last player to be reported as alive.  

Note :  
```
This is an alternative version of the original game. The virtual machine does not work the same way, and the assembly language is a bit different of the original Redcode, but the game spirit is still the same.

Original Core War wiki here : [Original Core War wiki page](https://en.wikipedia.org/wiki/Core_War)

This code has only been tested on macOS 10.11+
```

## Setting up and Usage

### Requirements

This project use `sdl`, `sdl_image` and `sdl_ttf` libraries.  

In order to get the program compile properly you have to install them.  
You can use [homebrew](https://brew.sh) to simply do this with :  
```sh
$ brew install sdl sdl_image sdl_ttf
```

### Compiling

First, clone and pull the submodules
```sh
$ git clone https://github.com/bil0u/corewar.git
...
$ git submodule update --init
```

The main Makefile has several rules:  

* `all`  
   Calls `lib`, `asm` and `vm` rules
* `lib`  
   Compile only the `libft` submodule
* `asm`  
   Compile the `libft` if needed and build the `asm` binary
* `vm`  
   Compile the `libft` if needed and build the `corewar` binary
* `champs`  
   Build the `asm` if not existing and use it to compile all `.s` files in the `champs` directory
* `tests`  
   Build the `asm` if not existing and use it to compile all `.s` files in the `champs` directory
* `clean`  
   Delete all `.o` & `.cor` files
* `fclean`  
   Calls the `clean` rule and delete `asm` & `corewar` binaries
* `re`  
   Calls `fclean` and `all` rules
* `norm`  
   Runs the `norminette` command on all the `sources` and `includes` subdirectories (Works only in 42 clusters)

## Modules

### Assembler

### Virtual machine

## Some screen captures

* Visualizer start screen  
   ![Visualizer](./demo/visualizer.png)  

* Debug level 1 : Game status  
   ![Game status](./demo/game_status.png)  

* Debug level 2 : Arena content  
   ![Arena](./demo/arena.png)  

* Debug level 4 : Instructions history  
   ![Intructions history](./demo/ops_history.png)  

* Debug level 8 : Intructions details  
   ![Intructions details](./demo/ops_details.png)  

* Debug level 16 : Processes list & infos  
   ![Processes](./demo/processes.png)  

* Debug level 36 : Processes registers  
   ![Registers](./demo/registers.png)  

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.txt](LICENSE.txt) file for details
