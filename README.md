# generator

Zhan.Shi @ 2016-2020

## Introduction

Random graph dataset generators.

## Common Options

- `-s <n>`: scale, generate 2^n vertices.
- `-d <d>`: degree, generate 'd' edges per vertex in average.
- `-r <s>`: seed, generate random edges using different pseudo-random sequence.
- `-o <f>`: file, generate edge list as binary file.

Generated edges will output to console as strings if `-o` is omitted.

## Barabási–Albert (Preferential Attachment)

```
ba [options]
 -h:     ask for help
 -s:     scale,  default: 8
 -d:     degree, default: 8
 -r:     srand,  default: current time
 -o:     output, default: console
```

## Erdos-Renyi

```
er [options]
 -h:     ask for help
 -s:     scale,  default: 8
 -d:     degree, default: 8
 -r:     srand,  default: current time
 -o:     output, default: console
```

## Recursive Matrix

```
rmat [options]
 -h:     ask for help
 -s:     scale,  default: 8
 -d:     degree, default: 8
 -r:     srand,  default: current time
 -o:     output, default: console
```

## Small World

```
sw [options]
 -h:     ask for help
 -s:     scale,  default: 8
 -d:     degree, default: 8
 -t:     ratio,  default: 0.01
 -r:     srand,  default: current time
 -o:     output, default: console
```

## Utility Scripts

### cloned-subgraph-synthesis.sh

Synthetic Graph based on Cloned Subgraphs connected by a Core Graph.

### permutate.sh

Assign consecutive vertex IDs to input graph, or permutate vertex IDs with a map file that holds pre-assigned IDs.

