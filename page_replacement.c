#include <stdio.h>
#include <limits.h>
int nframes, nstr;

void FIFO(int RefStr[], int Mem[]){
    int i,j,k,firstIn = 0,exists=0,x=0,nmiss=nstr;
    
    for(i=0; i<nstr; i++){
        for(j=0;j<nframes;j++){
            //checking if the page is present in memory
            if(RefStr[i] == Mem[j]){
                exists = 1;
                break;
            }
                
        }
        //if page is not in memory,
        if(exists==0){                          
            if(x<nframes){                     //if the not all frames are occupied,
                Mem[x] = RefStr[i];             
                x++;
            }
            else{                               //if all frames are oocupied then -> replace
                Mem[firstIn] = RefStr[i];
                firstIn = (firstIn+1)%nframes;
            }
        }
        //printing frames
        for(k=0;k<nframes;k++){
            if(Mem[k] == -1)
                printf("-");
            else 
                printf("%d ",Mem[k]);     
        }
        if(exists == 0)
            printf(" Miss\n");
        else{
            printf(" Hit\n");
            nmiss--;
        }
            
        exists = 0;
               
    }
    printf("\nPage fault ratio=%d/%d\n",nmiss,nstr);

}

void LRU(int RefStr[], int Mem[]){
    int i,j,k,leastUsed,exists=0,x=0,nmiss=nstr,loc=INT_MAX;
    
    for(i=0; i<nstr; i++){
        for(j=0;j<nframes;j++){
            if(RefStr[i] == Mem[j]){
                exists = 1;
                break;
            }
                
        }
        if(exists==0){
            if(x<nframes){
                Mem[x] = RefStr[i];
                x++;
            }
            else{
               for(j=0;j<nframes;j++){ 
                for(k=i-1;k>=0;k--){
                    if(Mem[j] == RefStr[k]){
                        if(k<loc){
                            loc = k;
                            break; 
                        }   
                        else    
                            break;  
                    }     
                }
               }
               for(j=0;j<nframes;j++){
                if(RefStr[loc] == Mem[j])
                    Mem[j] = RefStr[i];
               }
               loc = INT_MAX; 
            }
        }
        for(k=0;k<nframes;k++){
            if(Mem[k] == -1)
                printf("-");
            else 
                printf("%d ",Mem[k]);     
        }
        if(exists == 0)
            printf(" Miss\n");
        else{
            printf(" Hit\n");
            nmiss--;
        }
            
        exists = 0;
               
    }
    printf("\nPage fault ratio=%d/%d\n",nmiss,nstr);

}

void InitFrames(int Mem[]){
    for(int i=0; i<nframes; i++){
        Mem[i] = -1;
    }
}

void main(){
    int ch;
    printf("Enter number of frames:\n");
    scanf("%d",&nframes);
    int Mem[nframes];
    printf("Enter number of ref str size:\n");
    scanf("%d",&nstr);
    int RefStr[nstr];
    printf("Enter ref str:\n");
    for(int i=0; i<nstr; i++)
        scanf("%d",&RefStr[i]);
    do{
        printf("\nEnter choice:\n1.FIFO\n2.LRU\n3.Exit\n");
        scanf("%d",&ch);
        if(ch!=3)
            InitFrames(Mem);
        switch(ch){
            case 1:
                FIFO(RefStr,Mem);
                break;
            case 2:
                LRU(RefStr,Mem);
                break;
            case 3:
                break;
        }
    }while(ch!=3);
    
    
}