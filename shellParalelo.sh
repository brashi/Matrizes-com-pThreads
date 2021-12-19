#!/bin/bash

#SBATCH --partition=cluster
#SBATCH --job-name=HistoPth
#SBATCH --output=HistoPth.out
#SBATCH --error=HistoPth.err
#SBATCH --time=0-04:30
#SBATCH --hint=compute_bound 

#SBATCH --mem=12000
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32
rm Resultados/pth_histo*
rm Pth_Registro_Mat.txt
rm Paralelo
[ -d /Resultados ] || mkdir Resultados

make

	tentativas=20 #Quantas vezes o código será executado

	for cores in C S #Execução de Serial a Concorrente
	do
			for size in 4 16 32 64 128 256 512 1024 2048 #tamanho do problema
			do   	
				echo -e "\n$cores\t$size\t\t\c" >> "Pth_Registro_Mat.txt" 
				for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
				do
					./matmulti $size $cores #atualizar de acordo com OpenMP
				done
			done

	done
	 
	exit
