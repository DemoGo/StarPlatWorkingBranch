#include"sssp_dslV2.h"

void Compute_SSSP(graph& g,int* dist,int* weight,int src
)
{
  bool* modified=new bool[g.num_nodes()];
  bool* modified_nxt=new bool[g.num_nodes()];

  #pragma acc data copyin(g)
  {
    #pragma acc data copyout( modified[0: g.num_nodes()], modified_nxt[0: g.num_nodes()], dist[0: g.num_nodes()+1] )
    {
      #pragma acc parallel loop
      for (int t = 0; t < g.num_nodes(); t ++) 
      {
        dist[t] = INT_MAX;
        modified[t] = false;
        modified_nxt[t] = false;
      }
    }
  }

  modified[src] = true;
  dist[src] = 0;
  bool finished = false;
  #pragma acc data copyin(g)
  {
    #pragma acc data copyin( g.edgeList[0:g.num_edges()], g.indexofNodes[:g.num_nodes()+1], weight[0: g.num_edges()], modified[0: g.num_nodes()],  modified_nxt[0:g.num_nodes()] ) copy(dist[0:g.num_nodes()])
    {
      while ( !finished )
      {
        finished = true;
        #pragma acc data copy(finished)
        {
          #pragma acc parallel loop
          for (int v = 0; v < g.num_nodes(); v ++) 
          {
            if (modified[v] == true )
              {
              for (int edge = g.indexofNodes[v]; edge < g.indexofNodes[v+1]; edge ++) 
              {int nbr = g.edgeList[edge] ;
                int e = edge;
                 int dist_new = dist[v] + weight[e];
                bool modified_new = true;
                if(dist[nbr] > dist_new)
                {
                  int oldValue = dist[nbr];
                  #pragma acc atomic write
                    dist[nbr]= dist_new;

                  modified_nxt[nbr] = modified_new;
                  #pragma acc atomic write
                      finished = false;
                }
              }
            }
          }

          #pragma acc parallel loop
          for (int v = 0; v < g.num_nodes(); v ++) 
          { modified[v] =  modified_nxt[v] ;
            modified_nxt[v] = false ;
          }
        }
      }
    }
  }
}

}