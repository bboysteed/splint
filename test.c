 #include "Apath.h" 
  3 LinkList InitList()
  4 {
  5     LinkList L = (LinkList)malloc(sizeof(LNode));
  6     if (L == NULL)
  7     {
  8         printf("Defeat!");
  9         exit(1);
 10     }
 11     memset(L, 0, sizeof(LNode));
 12 
 13     return L;
 14 }//LinkList()
 15 
 16 LNode** malloc_array2D(int row, int col)
 17 {
 18     LNode** map = (LNode**)malloc(row * sizeof(LNode*) + row * col * sizeof(LNode));
 19     LNode* head = (LNode*)(map + row);
 20     for (int i = 0; i < row; ++i)
 21         map[i] = head + i * col;
 22 
 23     return map;
 24 }
 25 
 26 LNode** Translate_array(int array[][10], int row, int col)
 27 {
 28     LNode **map = malloc_array2D(10, 10);
 29     for (int i = 0; i < row; ++i)
 30         for (int j = 0; j < col; ++j)
 31         {
 32             (map[i] + j)->data = array[i][j];
 33             (map[i] + j)->G = 0;
 34             (map[i] + j)->H = 0;
 35             (map[i] + j)->F = 0; //(map[i] + j)->G + (map[i] + j)->H;
 36             (map[i] + j)->x = i;
 37             (map[i] + j)->y = j;
 38             (map[i] + j)->Close_flag = 0;
 39             (map[i] + j)->OPen_flag = 0;
 40             (map[i] + j)->next = NULL;
 41             (map[i] + j)->path_next = NULL;
 42         }
 43     return map;
 44 }
 45 
 46 void free_array2D(LNode **arr)
 47 {
 48     free(arr);
 49 }
 50 
 51 //二维数组的访问必须指明位数，否则编译器不能解析
 52 void output(LNode** array, int row, int col)
 53 {
 54     //for (int i = 0; i < row; ++i)
 55     // for (int j = 0; j < col; ++j)
 56     // {
 57     // (array[i] + j)->F = j;
 58     // }
 59     for (int i = 0; i < row; ++i)
 60     {
 61         for (int j = 0; j < col; ++j)
 62         {
 63             printf("%d\t", (array[i] + j)->data);
 64         }
 65         printf("\n");
 66     }
 67 
 68     for (int i = 0; i < row; ++i)
 69     {
 70         for (int j = 0; j < col; ++j)
 71         {
 72             printf("(%d,%d),%d\t", i, j, (array[i] + j)->data);
 73         }
 74         printf("\n");
 75     }
 76 }
 77 
 78 //从数组中找到始点
 79 LNode* find_start_LNode(LNode** Arr, int row, int col)
 80 {
 81     LNode* start_LNode = NULL;
 82     for (int i = 0; i < row; ++i)
 83     {
 84         for (int j = 0; j < col; ++j)
 85         {
 86             if (2 == (Arr[i] + j)->data)
 87             {
 88                 start_LNode = (Arr[i] + j);
 89                 //起点H=0,G=0,F=0
 90                 start_LNode->G = 0;
 91                 start_LNode->H = 0;
 92                 start_LNode->F = 0; //起点，则默认所有值为0
 93                 return start_LNode; //返回节点
 94             }
 95         }
 96     }
 97     return NULL;
 98 }
 99 
100 //从数组中找到终点
101 LNode* find_end_LNode(LNode** Arr, int row, int col)
102 {
103     LNode* end_LNode = NULL;
104     for (int i = 0; i < row; ++i)
105     {
106         for (int j = 0; j < col; ++j)
107         {
108             if (3 == (Arr[i] + j)->data)
109             {
110                 end_LNode = (*(Arr + i) + j);
111                 end_LNode->F = 0;
112                 end_LNode->G = 0;
113                 end_LNode->H = 0;
114                 return end_LNode; //返回节点
115             }
116         }
117     }
118     return NULL;
119 }
120 
121 //计算节点的G值
122 int count_LNode_G(LNode* curLNode, LNode* aheadLNode)
123 {
124     if (curLNode->x == aheadLNode->x && curLNode->y == aheadLNode->y)
125         return 0;
126 
127     if (aheadLNode->x - curLNode->x != 0 && aheadLNode->y - curLNode->y != 0)
128         curLNode->G = aheadLNode->G + 14;
129     else
130         curLNode->G = aheadLNode->G + 10;
131     return curLNode->G;
132 }
133 
134 //计算节点的H值
135 int count_LNode_H(LNode* curLNode, LNode* endLNode)
136 {
137     curLNode->H = abs(endLNode->x - curLNode->x) * 10 + abs(endLNode->y - curLNode->y) * 10;
138     return curLNode->H;
139 }
140 
141 //计算节点的F值
142 int count_LNode_F(LNode* curLNode)
143 {
144     curLNode->F = curLNode->G + curLNode->H;
145     return curLNode->F;
146 }
147 
148 //按从小到大的顺序
149 void push_OpenList_Node(LinkList L, LNode *elem)
150 {
151     LNode *p, *q;
152     p = q = L;
153     while (p->next != NULL && p->F < elem->F)
154     {
155         q = p;
156         p = p->next;
157     }
158 
159     if (p->F < elem->F)
160         q = p;
161 
162     elem->next = q->next;
163     q->next = elem;
164     //插入成功，更改属性值OPen_flag = 1
165     elem->OPen_flag = 1;
166 }
167 
168 //返回开放列表中F值最小的节点
169 LNode* pop_OpenList_minNode(LinkList L_OpenList)
170 {
171     LNode *elem = NULL;
172     if (L_OpenList->next) //为了安全，防止访问空指针
173     {
174         L_OpenList->next->OPen_flag = 0;
175         elem = L_OpenList->next;
176         L_OpenList->next = L_OpenList->next->next;
177         elem->next = NULL;
178     }
179     else
180         printf("have a NULL point in pop_OpenList_mimNode()");
181     return elem;
182 }
183 
184 //插入OpenList中F值最小的节点到CloseList中去
185 bool insert_Into_CloseList(LNode* min_Open, LinkList L_CloseList)
186 {
187     //对于CloseList中的节点并不需要排序,采用头插法
188     min_Open->next = L_CloseList->next;
189     L_CloseList->next = min_Open;
190     min_Open->Close_flag = 1;
191     return TURE;
192 }
193 
194 
195 bool isExist_openList(LNode* curLNode)
196 {
197     return curLNode->OPen_flag;
198 }
199 
200 bool isExist_closeList(LNode* curLNode)
201 {
202     return curLNode->Close_flag;
203 }
204 
205 bool isobstacle(LNode* curLNode)
206 {
207     if (curLNode->data == 1)
208         return TURE;
209     else
210         return FAULT;
211 }
212 
213 //该节点是否可以加入开放列表
214 bool CanJoinOpenList(LNode* cur)
215 {
216     if (cur->x > -1 && cur->y > -1) //边界检测
217     {
218         if (!isExist_closeList(cur) && !isobstacle(cur)) //既不在关闭列表里，也不是障碍物
219         {
220             return TURE;
221         }
222         else
223             return FAULT;
224     }
225     return FAULT;
226 }
227 
228 void insert_open(LNode *Node, LNode* ahead, LNode* endLNode, LinkList open_list, LNode** Arr)
229 {
230     if (!CanJoinOpenList(Node))
231         return;
232 
233     if (isExist_openList(Node))
234     {
235         //经由ahead节点，会不会使得F的值更小
236         if (Node->x - ahead->x != 0 && Node->y - ahead->y != 0)
237         {
238             if (Node->F > (ahead->F + 14))
239             {
240                 count_LNode_G(Node, ahead);
241                 count_LNode_F(Node); //H值没有改变，所以还是原来的值
242                 Node->path_next = ahead; //也不用再插入
243             }
244         }
245         else
246         {
247             if (Node->F > (ahead->F + 10))
248             {
249                 count_LNode_G(Node, ahead);
250                 count_LNode_F(Node); //H值没有改变，所以还是原来的值
251                 Node->path_next = ahead; //也不用再插入
252             }
253         }
254     }
255     else 
256     {
257         count_LNode_G(Node, ahead);
258         count_LNode_H(Node, endLNode);
259         count_LNode_F(Node);
260         Node->path_next = ahead;
261         push_OpenList_Node(open_list, Node);
262     }
263 }
264 
265 void check_around_curNode(LNode* cur, LNode* endLNode, LinkList open_list, LNode** Arr)
266 {
267     const int x = cur->x;
268     const int y = cur->y;
269 
270     //检查边界，画图标记下已经检查的节点
271     if (y + 1 < MAP_MAX_Y)
272     {
273         insert_open(Arr[x] + y + 1, cur, endLNode, open_list, Arr);
274 
275         if (x + 1 < MAP_MAX_X)
276             insert_open(Arr[x + 1] + y + 1, cur, endLNode, open_list, Arr);
277 
278         if(x - 1 >= 0)
279             insert_open(Arr[x - 1] + y + 1, cur, endLNode, open_list, Arr);
280     }
281 
282     if (x + 1 < MAP_MAX_X)
283     {
284         insert_open(Arr[x + 1] + y, cur, endLNode, open_list, Arr);
285 
286         if(y - 1 >= 0)
287             insert_open(Arr[x + 1] + y - 1, cur, endLNode, open_list, Arr);
288     }
289 
290     if (y - 1 >= 0)
291     {
292         insert_open(Arr[x] + y - 1, cur, endLNode, open_list, Arr);
293 
294         if (x - 1 >= 0)
295             insert_open(Arr[x - 1] + y - 1, cur, endLNode, open_list, Arr);
296     }
297 
298     if (x - 1 >= 0)
299         insert_open(Arr[x - 1] + y, cur, endLNode, open_list, Arr);
300 
301     //insert_open(Arr[x] + y - 1, cur, endLNode, open_list, Arr);
302     //insert_open(Arr[x] + y + 1, cur, endLNode, open_list, Arr);
303     //insert_open(Arr[x + 1] + y, cur, endLNode, open_list, Arr);
304     //insert_open(Arr[x + 1] + y - 1, cur, endLNode, open_list, Arr);
305     //insert_open(Arr[x + 1] + y + 1, cur, endLNode, open_list, Arr);
306     //insert_open(Arr[x - 1] + y, cur, endLNode, open_list, Arr);
307     //insert_open(Arr[x - 1] + y + 1, cur, endLNode, open_list, Arr);
308     //insert_open(Arr[x - 1] + y - 1, cur, endLNode, open_list, Arr);
309 }

Apath.c
