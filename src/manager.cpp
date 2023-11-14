#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include "manager.h"
#include "parser.h"

//Para debug
template <typename T>
void print_graph(std::vector<std::pair<int,std::vector<T>>> vec){
    for(const auto& i : vec){
        std::cout<<i.first<<": ";
        for(const auto& j : i.second){
            std::cout<<j<<' ';
        }
        std::cout<<std::endl;
    }
}

/**
 * Esta função é responsável por inicializar nosso grafo
 * de acordo com o arquivo solicitado pelo usuário
 */
void Manager::initialize(){
    //reseta as partições
    solucao.clear();
    //enquanto um teste não for escolhido
    while(!execute) display_initialization();
    //inicializa com o nome do arquivo selecionado
    initialize(file_name);
};

/**
 * Esta função é responsável por inicializar nosso grafo
 * de acordo com o arquivo solicitado pelo usuário a partir
 * do nome do arquivo solicitado por ele
 */
void Manager::initialize(std::string file_name){
    //reseta as partições
    solucao.clear();
    //lê o arquivo file_name e gera o grafo
    Parser p(file_name);
    grafo = p.get_grafo();
    n_arestas = p.get_edges();
    n_vertices = p.get_vertices();
};

int Manager::get_vertices(){
    return n_vertices;
}
int Manager::get_arestas(){
    return n_arestas;
}

/**
 * Método que colore o grafo e exibe as partições geradas
 */
void Manager::solve(){
    //cronometra
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    controle_ET();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    tempo = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    display_solution();
};

int Manager::get_colors(){
    return n_colors;
}



/**
 * Pede o arquivo e determina qual(is) teste(s) serão executados
 */
void Manager::display_initialization(){
    std::cout<<"Bem-vindo(a) à nossa implementação do algoritmo de Welsh-Powell!\n"
             <<"\n1 - Casos de teste disponíveis\n"
             <<"2 - Referências dos casos de teste\n"
             <<"Por favor, digite qual dos dois gostaria de ver > ";
    //comando do usuário
    char com;
    std::cin >> com;
    //pediu para executar os testes
    if(com == '1'){
        std::cout<<"\nNós temos 58 casos de teste disponíveis. Por este motivo, caso deseje mais detalhes sobre um \n"
                 <<"deles ou deseje executar algum, digite um número de 1 a 59. Caso deseje executar todos os testes,\n"
                 <<"digite 0 > ";
        //índice do teste
        int idx;
        std::cin >> idx;
        //se um teste foi pedido
        if(idx){
            //gera o grafo do arquivo requisitado
            Parser p(idx);
            //se o grafo for nulo, o arquivo não foi encontrado
            if(p.get_grafo().empty()) return;
            //senão, mostra os dados lidos ao usuário
            file_name = p.get_file_name();
            std::cout<<"\nNome do arquivo: "<<file_name<<std::endl;
            std::cout<<"Número de vértices: "<<p.get_vertices()<<std::endl;
            std::cout<<"Número de arestas: "<<p.get_vertices()<<std::endl;
            std::cout<<"\nDeseja executar este teste? \n(Atenção: cada linha da saída representa uma cor)\n(A saída e o tempo gasto também ficarão registrados no arquivo \"result.txt\") [Y/n] > ";
            //se o usuário deseja ou não executar aquele teste
            char ex;
            std::cin>>ex;
            //executará se o usuário digitar algo diferente de 'n' ou 'N'
            execute = (std::tolower(ex) != 'n');
        //caso o usuário tenha solicitado a execução de todos os testes
        } else {
            //guarda que todos serão executados
            all = true;
            execute = true;
            //todos os arquivos
            std::vector<std::string> file_names{"original.col","anna.col", "david.col", "fpsol2.i.1.col", "fpsol2.i.2.col", "fpsol2.i.3.col", "games120.col", "homer.col", "huck.col", "inithx.i.1.col", "inithx.i.2.col", "inithx.i.3.col", "latin_square_10.col", "jean.col", "le450_5a.col", "le450_5b.col", "le450_5c.col", "le450_5d.col", "le450_15a.col", "le450_15b.col", "le450_15c.col", "le450_15d.col", "le450_25a.col", "le450_25b.col", "le450_25c.col", "le450_25d.col", "miles250.col", "miles500.col", "miles750.col", "miles1000.col", "miles1500.col", "mulsol.i.1.col", "mulsol.i.2.col", "mulsol.i.3.col", "mulsol.i.4.col", "mulsol.i.5.col", "myciel2.col", "myciel3.col", "myciel4.col", "myciel5.col", "myciel6.col", "myciel7.col", "queen5_5.col", "queen6_6.col", "queen7_7.col", "queen8_8.col", "queen8_12.col", "queen9_9.col", "queen10_10.col", "queen11_11.col", "queen12_12.col", "queen13_13.col", "queen14_14.col", "queen15_15.col", "queen16_16.col", "school1.col", "school1_nsh.col", "zeroin.i.1.col", "zeroin.i.2.col", "zeroin.i.3.col"};
            //índice do teste atual
            curr_idx = 0;
            //passa por cada arquivo
            for(const auto& i : file_names){
                grafo.clear();
                ++curr_idx;
                //inicializando de acordo com o nome do arquivo
                initialize(i);
                //e executando o algoritmo no grafo lido
                solve();
            }
        }
    //caso o usuário peça para ver as referências dos testes
    } else {
        std::cout   <<"REG: (De Gary Lewandowski (gary@cs.wisc.edu)) Problema baseado na alocação de registros para variáveis em códigos reais.\n"
                    <<"LEI: (De Craig Morgenstern (morgenst@riogrande.cs.tcu.edu)) Grafos de Leighton com tamanho de coloração garantido. A referência\n"
                    <<"é F.T. Leighton, Journal of Research of the National Bureau of Standards, 84: 489--505 (1979).\n\n"
                    <<"SCH: (De Gary Lewandowski (lewandow@cs.wisc.edu)) Grafos de marcar aulas, com e sem salas de estudo.\n\n"
                    <<"LAT: (De Gary Lewandowski (lewandow@cs.wisc.edu)) Problema do quadrado latino.\n\n"
                    <<"SGB: (De Michael Trick (trick@cmu.edu)) Grafos da base de grafos de Stanford de Donald Knuth (Donald \n"
                    <<"Knuth's Stanford GraphBase). Podem ser divididos em:\n\n"
                    <<"\tGrafos de livro. Dada uma obra da literatura, um grafo em que cada nó representa um personagem é criado.\n" 
                    <<"\tDois nós são conectados por uma aresta se os personagens correspondentes se encontram no livro.\n"
                    <<"\tKnuth cria os grafos para cinco obras clássicas: Anna Karenina de Tolstoy (anna), David Copperfield de Dickens\n" 
                    <<"\t(david), A Ilíada de Homero (homer), Huckleberry Finn (huck) de Twain e Os Miseráveis de Hugo (jean).\n\n"
                    <<"\tGrafos de jogos. Um grafo representando os jogos de uma temporada de futebol em uma faculdade pode ser \n"
                    <<"\tum grafo em que os nós representam cada equipe da faculdade. Dois times se conectam por uma aresta se eles\n"
                    <<"\tjogaram um contra o outro na temporada. Knuth dá o grafo para a temporada de futebol universitário de 1990.\n\n"
                    <<"\tGrafos de milhas. Estes grafo são semelhantes a grafos geométricos em que os nós são colocados no espaço e \n"
                    <<"\tdois nós se conectam se estão próximos o suficiente. Estes grafos, no entanto, não são aleatórios. Os nós são \n"
                    <<"\tum conjunto de cidades dos Estados Unidos e a distância entre eles é dada pela distância em milhas de 1947. \n"
                    <<"\tEstes grafos também existem graças a Knuth.\n\n"
                    <<"\tGrafos de dama. Dado um tabuleiro de xadrez n por n, um grafo de dama é um grafo de n^2 nós, cada um correspondendo\n"
                    <<"\ta um quadrado do tabuleiro. Dois nós se conectam por uma aresta se o quadrado correspondente se encontra na mesma \n"
                    <<"\tlinha, coluna ou diagonal. Diferente de alguns outros grafos, o problema de coloração neste grafo tem uma \n"
                    <<"\tinterpretação natural: Dado tal tabuleiro, é possível colocar n conjuntos de n damas no tabuleiro de modo que\n"
                    <<"\tnão haja duas damas do mesmo conjunto na mesma linha, coluna ou diagonal? A resposta é sim se e somente se o grafo\n"
                    <<"\ttem número de coloração n. Martin Gardner afirma sem provas que este é o caso se e somente se n não é divisível nem\n"
                    <<"\tpor 2 nem por 3. Em qualquer caso, a clique máxima no grafo não é maior que n e o valor de coloração não é menor que n.\n\n"
                    <<"MYC: (De Michael Trick (trick@cmu.edu)) Grafos baseados na transformação de Mycielski. Estes grafos são difíceis de\n" 
                    <<"resolver porque eles são \"triangle free\" (clique número 2), mas o número de coloração aumenta o tamanho do problema."<<std::endl;

        std::cout<<std::endl<<"Digite 's' para sair > ";
        char s;
        std::cin>>s;
        
    }

};

void Manager::display_simple(){
    // std::ofstream out;
    // out.open("results/result.txt");
    std::vector<std::string> file_names{"original.col","anna.col", "david.col", "fpsol2.i.1.col", "fpsol2.i.2.col", "fpsol2.i.3.col", "games120.col", "homer.col", "huck.col", "inithx.i.1.col", "inithx.i.2.col", "inithx.i.3.col", "latin_square_10.col", "jean.col", "le450_5a.col", "le450_5b.col", "le450_5c.col", "le450_5d.col", "le450_15a.col", "le450_15b.col", "le450_15c.col", "le450_15d.col", "le450_25a.col", "le450_25b.col", "le450_25c.col", "le450_25d.col", "miles250.col", "miles500.col", "miles750.col", "miles1000.col", "miles1500.col", "mulsol.i.1.col", "mulsol.i.2.col", "mulsol.i.3.col", "mulsol.i.4.col", "mulsol.i.5.col", "myciel2.col", "myciel3.col", "myciel4.col", "myciel5.col", "myciel6.col", "myciel7.col", "queen5_5.col", "queen6_6.col", "queen7_7.col", "queen8_8.col", "queen8_12.col", "queen9_9.col", "queen10_10.col", "queen11_11.col", "queen12_12.col", "queen13_13.col", "queen14_14.col", "queen15_15.col", "queen16_16.col", "school1.col", "school1_nsh.col", "zeroin.i.1.col", "zeroin.i.2.col", "zeroin.i.3.col"};
    // std::cout<<curr_idx<<" | ";
    std::cout<<file_names[curr_idx-1]<<" & "<<n_vertices<<" & "<<n_arestas<<" & "<<n_colors<<" & "<<tempo.count()<<" \\\\\n";
}

/**
 * Mostra as partições geradas
 */
void Manager::display_solution(){
    //Caso não haja solução para a coloração daquele grafo
    if(!found_solution){
        std::cout<<"Ops! Não conseguimos encontrar uma solução para o seu problema :("<<std::endl;
        return;
    }
    //arquivo onde serão impressas a solução, o tempo e as cores usadas
    std::ofstream out;
    //caso só vá ser executado um teste
    if(!all) out.open("results/result.txt");
    //caso sejam todos a serem executados
    else out.open("results/result" + std::to_string(curr_idx) + ".txt");
    //percorre cada partição, imprimindo cada vértice dela
    for(const auto& i : solucao){
        for(const auto& j : i){
            std::cout<<j+1<<' ';
            out << j+1 <<' ';
        }
        //não imprime partições vazias
        if(!i.empty()){
            std::cout<<std::endl<<std::endl;
            out << std::endl<<std::endl;
        }
    }
    //imprime tempo e cores
    std::cout<<"Tempo (em ms): "<<tempo.count()<<std::endl;
    out << "Tempo (em ms): "<<tempo.count()<<std::endl;
    std::cout<<"Número de cores usadas: "<<n_colors<<std::endl;
    out<<"Número de cores usadas: "<<n_colors<<std::endl;
};


/*
 * Checa se a interseção entre dois vetores ordenados é vazia
 */
template <typename T>
bool empty_intersection(std::vector<T> a, std::vector<T> b){
    for(auto i1{0u}, i2{0u}; i1 < a.size() && i2 < b.size();){
        //se há um elemento em comum
        if(a[i1] == b[i2]) return false;
        //avança o índice no vetor com menor número
        else if(a[i1] < b[i2]) ++i1;
        else if(a[i1] > b[i2]) ++i2;
    }
    return true;
}

/**
 * Retorna índice do vértice de maior grau
 */
template <typename T>
int greatest_degree(std::vector<T> a){
    auto maior{0};
    for(auto i{0u}; i < a.size(); ++i){
        if(a[i].second.size() > a[maior].second.size()) maior = i;
    }
    return maior;
}

/**
 * Algoritmo usado para colorir nosso grafo
 * seguindo as restrições dadas
 */
void Manager::welsh_powell(){
    //se o vértice foi colorido ou não
    bool colored;

    //ordenando vértices com base em seu grau
    std::sort(grafo.begin(), grafo.end(), 
              [](const std::pair<int,std::vector<int>>& a, const std::pair<int,std::vector<int>>& b) 
              {return a.second.size() > b.second.size();});
    auto n_cores{grafo.size()};
    //já começamos com no mínimo uma cor
    n_colors = 1;
    //cria cada partição de cor
    for(auto i{0u}; i<n_cores; ++i) solucao.emplace_back();
    //primeiro vértice é colorido com a primeira cor
    solucao[0].push_back(grafo[0].first);
    //para cada vértice não-colorido
    for(auto i{1u}; i<grafo.size(); ++i){
        //cada um começa como não-colorido
        colored = false;
        //para cada partição de cores
        for(auto& j : solucao){ 
            //se os adjacentes do vértice i já não estão da cor j
            if (empty_intersection(grafo[i].second, j)) {
                colored = true;
                //se é uma cor nova, o número de cores aumenta
                if(j.empty()) ++n_colors;
                //colore o vértice i da cor j
                j.push_back(grafo[i].first);
                //preciso do nome do vértice ordenado para checar a interseção
                std::sort(j.begin(), j.end());
                //se foi colorido, podemos ir para o próximo vértice
                break;
            }
        }
        //se um vértice não pôde ser colorido, não há solução
        if(!colored){
            found_solution = false;
            return;
        }
    }
    //se chegamos aqui, colorimos todos os vértices
    found_solution = true; 
};

/**
 * Algoritmo autoral usado para colorir nosso 
 * grafo seguindo as restrições dadas
 */
void Manager::albuquerque_wanderley(){
    //vértices coloridos
    std::vector<bool> colored(grafo.size(), false);

    //iniciando a colorir pelo vértice de maior grau
    auto v{greatest_degree(grafo)};

    auto n_cores{grafo.size()};
    //já começamos com no mínimo uma cor
    n_colors = 1;
    //cria cada partição de cor
    for(auto i{0u}; i<n_cores; ++i) solucao.emplace_back();
    //vértice de maior grau é colorido com a primeira cor
    solucao[0].push_back(v);
    colored[v] = true;

    std::queue<unsigned long long int> q;
    q.push(v);

    while (!q.empty()){
        v = q.front();
        q.pop();
        for(auto w : grafo[v].second){
            if(!colored[w]){
                for(auto& j : solucao){ 
                    //se os adjacentes do vértice i já não estão da cor j
                    if (empty_intersection(grafo[w].second, j)) {
                        colored[w] = true;
                        //se é uma cor nova, o número de cores aumenta
                        if(j.empty()) ++n_colors;
                        //colore o vértice w da cor j
                        j.push_back(grafo[w].first);
                        //preciso do nome do vértice ordenado para checar a interseção
                        std::sort(j.begin(), j.end());
                        //se foi colorido, podemos ir para o próximo vértice
                        break;
                    }
                }
                q.push(w);
            }
        }
    }
    found_solution = true;
}

void Manager::controle_ET(){
    std::vector<std::vector<int>> solucao_parcial;
    auto copy = grafo;
    n_colors = -1;
    for(auto j{0u}; j<grafo.size(); ++j) solucao_parcial.emplace_back();
    for(auto i : copy){
        ET(i, copy, solucao_parcial, 0);
    }
}

void Manager::ET(std::pair<int, std::vector<int>> vertice_atual, std::vector<std::pair<int, std::vector<int>>> vertices_nao_coloridos, std::vector<std::vector<int>> solucao_parcial, unsigned int numero_de_cores){
    //colorir
    for(auto& j : solucao_parcial){ 
        //se os adjacentes do vértice i já não estão da cor j
        if (empty_intersection(vertice_atual.second, j)) {
            auto rem{std::find(vertices_nao_coloridos.begin(), vertices_nao_coloridos.end(), vertice_atual)};
            vertices_nao_coloridos.erase(rem);
            //se é uma cor nova, o número de cores aumenta
            if(j.empty()) ++numero_de_cores;
            //colore o vértice da cor j
            j.push_back(vertice_atual.first);
            //preciso do nome do vértice ordenado para checar a interseção
            std::sort(j.begin(), j.end());
            //se foi colorido, podemos ir para o próximo vértice
            break;
        }
    }

    //verificação do caso-base
    if(!vertices_nao_coloridos.empty()){
        for (auto i : vertices_nao_coloridos){
            ET(i, vertices_nao_coloridos, solucao_parcial, numero_de_cores);
        }
        
    } else {
        found_solution = true;
        if(numero_de_cores < n_colors){
            n_colors = numero_de_cores;
            solucao = solucao_parcial;
        }
    }
}

void Manager::Zykov(){
    ColorZ(grafo);
}

std::pair<int, int> two_unlinked(std::vector<std::pair<int,std::vector<int>>> G){
    bool flasg;
    for(auto i : G){
        for(auto j : G){
            flasg = false;
            for(auto k : j.second){
                if(i.first == k){
                    flasg = true;
                }
            }
            if(!flasg){
                return std::pair<int, int>{i.first, j.first};
            }
        }
    }
    return std::pair<int, int>{-1, -1};
}

bool completo(std::vector<std::pair<int,std::vector<int>>>& G){
    return two_unlinked(G) == std::pair<int, int>{-1, -1};
}

void contract_vertices(std::vector<std::pair<int,std::vector<int>>>& G, std::pair<int, int> vertices){
    for(auto i : G[vertices.first].second){
        for(auto j : G[vertices.second].second){
            if(i != j){
                G[vertices.first].second.push_back(j);
            }
        }
    }
    G[vertices.second].first = vertices.first;
    G[vertices.second].second.clear();    
}

void add_edge(std::vector<std::pair<int,std::vector<int>>>& G, std::pair<int, int> vertices){
    G[vertices.first].second.push_back(vertices.second);
    G[vertices.second].second.push_back(vertices.first);
}

void Manager::ColorZ(std::vector<std::pair<int,std::vector<int>>> G){
    auto n{G.size()};
    if(completo(G)){
        std::cout<<n_colors;
        n_colors = n_colors < n ? n_colors : n;
    } else {
        std::vector<std::pair<int,std::vector<int>>> G1{G}, G2{G};
        std::pair<int, int> vertices_labels = two_unlinked(G);
        contract_vertices(G1, vertices_labels);
        add_edge(G2, vertices_labels);
        ColorZ(G1);
        ColorZ(G2);
    }
}

