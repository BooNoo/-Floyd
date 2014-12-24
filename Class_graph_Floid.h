//
//  graph.h
//  graph
//
//  Created by Vladimir Mikhaylov on 23.12.14.
//  Copyright (c) 2014 Vladimir Mikhaylov. All rights reserved.
//

#ifndef graph_graph_h
#define graph_graph_h
#include <set>
#include <queue>

using namespace::std;
class graph


{
  int const e = 323232;
    int **matrix_weight, **matrix_history, **matrix_weight_for_floid;
    int **matrix_weight_help, **matrix_history_help;
    int *top_vault, *top_vault_help;
    int matrix_step;
    int counter = 0;
    int help = 5 ; // can't be  <= 1!!!!!
    int make_bigger_counter =0;
    
public:
    
    graph()
    {
         matrix_weight = new int*[help];
        for ( int i = 0; i < help; i++)
        matrix_weight[i] = new int[help];
        
        matrix_weight_help = new int*[help];
        for ( int i = 0; i < help; i++)
        matrix_weight_help[i] = new int[help];
        
         top_vault = new int [help];
        top_vault_help = new int [help];
        
        matrix_history = new int*[help];
        for ( int i = 0; i < help; i++)
        matrix_history[i] = new int[help];
        
        matrix_history_help = new int*[help];
        for ( int i = 0; i < help; i++)
        matrix_history_help[i] = new int[help];
        
        for (int i = 0; i< help; i++) 
        {
          for (int j = 0; j< help; j++)
            {
            matrix_weight[i][j] = 0;
            matrix_weight_help[i][j] = 0;
            matrix_history[i][j] = 0;
            matrix_history_help[i][j] = 0;
            }
        }
     }
    
    ~graph()
    {
        delete matrix_weight;
        delete matrix_history;
        delete matrix_history_help;
        delete matrix_weight_help;
    }
    
     void make_matrix_bigger() // function of increasing dimension of the table
    {
        make_bigger_counter++;
        int f = 2 * help;
        
         for (int i =0; i < help; i++)
          {
          top_vault_help[i] = top_vault[i];
          }
        
        delete top_vault;
        
        top_vault = new int [f];
        for (int i =0; i < help; i++)
          {
          top_vault[i] = top_vault_help[i];
          }
        
        
      for (int i =0; i < help; i++) {
            for ( int j = 0; j < help; j++)
            {
                matrix_history_help[i][j] = matrix_history[i][j];
            }
        }
        delete [] matrix_history;
        matrix_history = new int*[f];
        for ( int i = 0; i < f; i++)
        matrix_history[i] = new int[f];
        for (int i =0; i<f; i++) {
            for ( int j = 0; j < f; j++)
            {
                matrix_history[i][j] = 0;
                // matrix_weight_help[i][j] = 0;
            }
        }
        for (int i =0; i<help; i++) {
            for ( int j = 0; j < help; j++)
                matrix_history[i][j] = matrix_history_help[i][j];
        }
        delete [] matrix_history_help;
        
        matrix_history_help = new int*[f];
        for ( int i = 0; i < f; i++)
        matrix_history_help[i] = new int[f];
        
       for (int i =0; i < help; i++) 
       {
            for ( int j = 0; j < help; j++)
            {
              matrix_weight_help[i][j] = matrix_weight[i][j];
            }
        }
       
        delete [] matrix_weight;
        matrix_weight = new int*[f];
        for ( int i = 0; i < f; i++)
        matrix_weight[i] = new int[f];
        for (int i =0; i<f; i++)
        {
            for ( int j = 0; j < f; j++)
            {
                matrix_weight[i][j] = 0;
               // matrix_weight_help[i][j] = 0;
            }
        }
        for (int i =0; i<help; i++) {
        for ( int j = 0; j < help; j++)
        matrix_weight[i][j] = matrix_weight_help[i][j];
        }
        delete [] matrix_weight_help;
        matrix_weight_help = new int*[f];
        for ( int i = 0; i < f; i++)
        matrix_weight_help[i] = new int[f];
        help = help *2;
     }
    
    
    void add_top(int top)
    {
        bool x;
        if ((x = search_in_top_vault_bool(top)))
            {
            cout<<endl<<"Такая вершина уже есть"<<endl;
                //counter--;
            }
          else
          {
           counter++;
            if (counter > help)
                 {
                  make_matrix_bigger();
                 }
              int x = search_in_top_vault_first_zero();
              top_vault[x] = top;
          }
    }
    bool search_in_top_vault_bool( int top)
    
    {
        bool x = false;
        for (int i = 0; i < help; i++)
        {
            if (top_vault[i] == top)
            {
                x = true ;
            }
        }
        return x;
    }

    
    int search_in_top_vault( int top)
    
    {
        int x = 0;
        for (int i = 0; i < help; i++)
            {
            if (top_vault[i] == top)
                {
                x = i;
                }
            }
        return x;
    }
    int search_in_top_vault_first_zero()
    {
        int x = 0;
        bool first = false;
        for (int i =0; i< help; i++) {
            if ((top_vault[i]== 0) && (first == false)) {
                x = i;
                first = true;
            }
        }
        return x;
    }
    
    
    void add_arch( int a, int b, int weight)
    {
        if (a !=b)
        {
          if (weight == e) 
          {
            cout<<"Это число зарезервированно"<<endl;
           }
           bool x = search_in_top_vault_bool(a);
           bool y = search_in_top_vault_bool(b);
           if (x == false)
            {
            cout<<endl<<endl<<"  Попытка связать дугой несуществующую вершину "<<a<<endl;
             }
           if (y == false)
           {
            cout<<endl<<endl<<"  Попытка связать дугой несуществующую вершину "<<b<<endl;
           }
          if (x && y)
          {
            int x = search_in_top_vault(a);
            int y = search_in_top_vault(b);
            if (matrix_weight[x][y] == 0 )
              {
                 matrix_weight[x][y] = weight;
                 matrix_history[x][y] = b;
               }
            else
              {
              cout<<endl<<"Такая дуга уже есть"<<endl;
              }
         }
        }
      else
        {
          cout<<endl<<"Нельзя связать две одинаковых вершины"<<endl;
        }
    }
    
    void delete_arch(int a, int b)
    {
        bool x = search_in_top_vault_bool(a);
        bool y = search_in_top_vault_bool(b);
        if (x == false)
        {
            cout<<endl<<endl<<"  Попытка удалить несуществующую дугу "<<endl;
        }
        if (y == false)
        {
            cout<<endl<<endl<<"   Попытка удалить несуществующую дугу "<<endl;
        }
        if (x && y)
          {
            int x = search_in_top_vault(a);
            int y = search_in_top_vault(b);
             if( matrix_weight[x][y] == 0)
             {
               cout<<endl<<"Нету такой дуги"<<endl;
             }
            else
            {
                if (matrix_weight[x][y] != e) 
                  {
                    matrix_weight[x][y] = 0;
                    matrix_history[x][y] = 0;
                 }
            }
         }
      }
    void print_top_vault()
    {
        cout<<endl<<endl<<"Вершины: ";
        for (int i = 0; i<help; i++)
            if (top_vault[i]!= 0)
            {
               cout<< top_vault[i]<<"  ";
            }
       cout<<endl;
    }
    
    
    void del_top(int top)
    {
        int x = search_in_top_vault(top);
        top_vault[x] = 0;
        counter--;
        for (int i = 0; i<help; i++)
          {
            matrix_weight[i][x] = 0;
            matrix_weight[x][i] = 0;
            matrix_history[i][x] = 0;
            matrix_history[x][i] = 0;
        }
    }
    
    void print_graph()
    {
        cout<<endl<<endl<<" Матрица смежности   ";
        cout<<endl<<endl<<"    ";
        for (int i= 0; i< help; i++) {
           cout<<"("<< top_vault[i]<<")  ";
        }
        
        for (int i = 0; i< help; i++) {
            cout<<endl;
            cout<<"("<<top_vault[i]<<")   ";
           for (int j = 0; j< help; j++)
           {
               cout<<matrix_weight[i][j]<<"   ";
           }
        }
    }
    
    
    void print_floid_matrix()
    {
        cout<<endl<<endl<<" Матрица Флойда   ";
        cout<<endl<<endl<<"    ";
        for (int i= 0; i< counter; i++) {
            cout<<"("<< top_vault[i]<<")  ";
        }
        
        for (int i = 0; i< counter; i++) {
            cout<<endl;
            cout<<"("<<top_vault[i]<<")   ";
            for (int j = 0; j< counter; j++)
            {
                cout<<matrix_weight_for_floid[i][j]<<"   ";
            }
        }
    }
    
    void print_graph_history()
    {
        cout<<endl<<endl<<" Матрица историй   ";
        cout<<endl<<endl<<"    ";
        for (int i= 0; i< help; i++) {
            cout<<"("<< top_vault[i]<<")  ";
        }
        
        for (int i = 0; i< help; i++) {
            cout<<endl;
            cout<<"("<<top_vault[i]<<")   ";
            for (int j = 0; j< help; j++)
            {
                cout<<matrix_weight_for_floid[i][j]<<"   ";
            }
        }
    }
    
    
    void print_make_bigger_count()
    {
        cout<<endl<<make_bigger_counter<<endl;
    }
    
    
    void obhod_v_shirinu(int unit)
    {
        cout<<endl<<endl<<" Обход в ширину  ";
        queue<int> q;
        set<int> passed;
        int i = 0;
        if ((i = search_in_top_vault(unit)) != e) {
            q.push(i);
            passed.insert(i);
            while (!q.empty()) {
                i = q.front();
                q.pop();
                cout<< this->top_vault[i] << ' ';
                for (int j = 0; j < help; j++) {
                    if ((this->matrix_weight[i][j]!=0)&& passed.find(j) == passed.end()) {
                        q.push(j);
                        passed.insert(j);
                    }
                }
            }
        } else cout<< "No such element\n";
        return;
    }
    
    void preparation_for_floid()
    {
        for (int i =0; i<help; i++)
        {
            for ( int j = 0; j < help; j++)
            {
            if ((i != j) && (matrix_weight_for_floid[i][j]== 0))
                    {
                        matrix_weight_for_floid[i][j] = e;
                    }
            }
        }
    }
    
    
    
    
    void make_beauty()
    {
        for (int i =0; i<help; i++)
        {
            for ( int j = 0; j < help; j++)
            {
                if (matrix_weight_for_floid[i][j] >3000)
                {
                    matrix_weight_for_floid[i][j] = 0;
                }
            }
        }
    }
    
    
    bool chec_for_mistake()
    {
        bool x = false;
        for (int i =0; i<help; i++)
        {
            if (matrix_weight_for_floid[i][i] != 0) 
            {
                x = true;
            }
        }
        return x;
    }
    
    void make_matrix_for_floid()
    {
        matrix_weight_for_floid = new int*[help];
        for ( int i = 0; i < help; i++)
            matrix_weight_for_floid[i] = new int[help];
        
        for (int i =0; i<help; i++)
        {
            for ( int j = 0; j < help; j++)
            {
                matrix_weight_for_floid[i][j] = matrix_weight[i][j];
            }
        }
        
        
    }
    
    void make_floid ()
    {
        delete [] matrix_weight_for_floid;
        bool exit;
        make_matrix_for_floid();
        preparation_for_floid();
        for (int i =0; i<counter; i++)
        {
            for ( int j = 0; j < counter; j++)
            {
                if ( (exit = chec_for_mistake()) == false)
                {
                 for (int k = 0; k<counter; k++)
                    {
                        if (matrix_weight_for_floid[j][k] > (matrix_weight_for_floid[j][i] + matrix_weight_for_floid[i][k]))
                        {
                            matrix_weight_for_floid[j][k] = (matrix_weight_for_floid[j][i] + matrix_weight_for_floid[i][k]);
                            matrix_history_help[j][k] = matrix_history_help[j][i];
                        }
                    }
                }
            }
          }
        
        if ((exit = chec_for_mistake()) == true )
        {
           cout<<endl<<"Выход из алгоритма!";
        }
        make_beauty();
    }
    
    
};
#endif
