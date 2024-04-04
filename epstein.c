 pai, Heap *heap)
 {
     Apontador q;

     q = grafo->listaAdj[pai];

     while (q != NULL)
     {

         q = q->prox;
     }
     while (grafo->listaAdj[pai] != NULL)
 }