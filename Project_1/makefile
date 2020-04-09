main2: main2.c count_mutual_links2.c read_graph_from_file2.c top_n_webpages.c
	gcc main2.c count_mutual_links2.c read_graph_from_file2.c top_n_webpages.c -I. -o main2.exe
	./main2.exe web-NotreDame.txt

main2_OMP: main2.c count_mutual_links2.c read_graph_from_file2.c top_n_webpages.c
	gcc -fopenmp main2.c count_mutual_links2.c read_graph_from_file2.c top_n_webpages.c -I. -o main2_OMP.exe
	./main2_OMP.exe web-NotreDame.txt

main1: main1.c count_mutual_links1.c read_graph_from_file1.c top_n_webpages.c
	gcc main1.c count_mutual_links1.c read_graph_from_file1.c top_n_webpages.c -I. -o main1.exe
	./main1.exe test.txt

main1_OMP: main1.c count_mutual_links1.c read_graph_from_file1.c top_n_webpages.c
	gcc -fopenmp main1.c count_mutual_links1.c read_graph_from_file1.c top_n_webpages.c -I. -o main1_OMP.exe
	./main1_OMP.exe test.txt

test: test_file.c count_mutual_links1.c read_graph_from_file1.c top_n_webpages.c count_mutual_links2.c read_graph_from_file2.c
	gcc test_file.c count_mutual_links1.c read_graph_from_file1.c top_n_webpages.c count_mutual_links2.c read_graph_from_file2.c -I. -o test_file.exe
	./test_file.exe test.txt

test_OMP: test_file.c count_mutual_links1.c read_graph_from_file1.c top_n_webpages.c count_mutual_links2.c read_graph_from_file2.c
	gcc -fopenmp test_file.c count_mutual_links1.c read_graph_from_file1.c top_n_webpages.c count_mutual_links2.c read_graph_from_file2.c -I. -o test_file.exe
	./test_file.exe p2p-Gnutella08.txt p2p-Gnutella08.txt