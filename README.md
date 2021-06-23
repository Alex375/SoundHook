# SoundHook

>Sound processing project for Epita S4

-------



## Dependencies

### FTTW3

#### Install

```sh
% brew install fftw
```


### GTK3

#### Install

```sh
% brew install gtk+3
```



## Build and lauch the project

>   Project is build with `CMake` you can build and launch the project with the CLion editor with a standard configuration or with command line.

### Build and run with command line

#### Build

```shell
% cmake . #A makefile is generated
% make 	  #Code target is compiled
```

#### Run the project

```shell
% ./mainUI #The graphic interface is launched
```



## Tasks

| Tasks                               | Aurore |  Noé  | Alexandre |
| :---------------------------------- | :----: | :---: | :-------: |
| Décodage fichier entré              |        |   +   |    ++     |
| Décomposition du son                |   +    |  ++   |           |
| Analyse du sons                     |        |  ++   |     +     |
| Recomposition du son avec traitment |   ++   |   +   |           |
| I/O                                 |   ++   |       |     +     |
| Interface graphique                 |   +    |       |    ++     |
| Site Web                            |   ++   |       |           |

## Planning

| Tasks                               |  S1   |  S2   |  S3   |
| :---------------------------------- | :---: | :---: | :---: |
| Décodage fichier entré              | [++-] | [+++] | [+++] |
| Décomposition du son                | [+--] | [++-] | [+++] |
| Analyse du sons                     | [---] | [+--] | [+++] |
| Recomposition du son avec traitment | [---] | [++-] | [+++] |
| I/O                                 | [+--] | [++-] | [+++] |
| Interface graphique                 | [---] | [+--] | [+++] |
| Site Web                            | [++-] | [+++] | [+++] |
