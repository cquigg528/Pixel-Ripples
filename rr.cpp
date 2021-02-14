/**
 * @file rr.cpp
 * Implementation of rainbowRipple.
 *
 * Modify and turn in this file for the PA!
 *
 */
#include "rr.h"


void ERROR_badGaps(string sgc) {
// Report error and exit.
//
  cerr << "ERROR: Unable to parse string specifying gaps and colors: "
       << "\"" << sgc << "\""
       << endl;
  exit(-1);
}

vector<pair<int,RGBAPixel>> parseGaps(string sgc) {
// Convert a string containing a sequence of number,character pairs,
// where number is an integer >= 0 and character is one of roygbiv,
// into a vector<pair<int,RGBAPixel>> of the sequence of pairs except
// the characters are replaced by the corresponding RGBAPixel.
// For example, the string "0r10g7b" converts to the vector
// [(0,RGBAPixel(255,0,0)),(10,RGBAPixel(0,255,0)),(7,RGBAPixel(0,0,255))]
//
//
//
  vector<pair<int,RGBAPixel>> vgc;
  RGBAPixel c;
  size_t idx = 0;
  size_t i = 0;
  int g;
  while( idx < sgc.size() ) {
    try {
      g = stoi(sgc.substr(idx), &i);
    } catch( invalid_argument& ia ) {
      ERROR_badGaps(sgc);
    }
    idx += i;
    if( g < 0 || idx >= sgc.size() ) ERROR_badGaps(sgc);
    switch( sgc[idx] ) {
    case 'R':
    case 'r':
      c =  RGBAPixel(255,0,0);	//red
      break;
    case 'O':
    case 'o':
      c = RGBAPixel(255,165,0);	//orange
      break;
    case 'Y':
    case 'y':
      c = RGBAPixel(255,255,0);	//yellow
      break;
    case 'G':
    case 'g':
      c = RGBAPixel(0,255,0);	//green
      break;
    case 'B':
    case 'b':
      c = RGBAPixel(0,0,255);	//blue
      break;
    case 'I':
    case 'i':
      c = RGBAPixel(75,0,130);	//indigo
      break;
    case 'V':
    case 'v':
      c = RGBAPixel(238,130,238);//violet
      break;
    default:
      ERROR_badGaps(sgc);
    }
    vgc.push_back(make_pair(g,c));
    idx++;
  }
  return vgc;
}

bool closeEnough(RGBAPixel c1, RGBAPixel c2) {
// Returns true iff color c1 is close enough to color c2
//
  int dist = (c1.r-c2.r)*(c1.r-c2.r) + (c1.g-c2.g)*(c1.g-c2.g) +
    (c1.b-c2.b)*(c1.b-c2.b);

  return (dist <= 80);
}

bool good(PNG & image, vector<vector<int>> & D,
		pair<int,int> curr, pair<int,int> next) {
// Returns true iff a neighbor "next" of a pixel "curr" is:
// 1. within the image,
// 2. unvisited, and
// 3. close in color to "curr".
// An entry in distance table D is -1 only if the pixel has not been 
// visited.

// only access D if coordinates of next are within the image
if (next.first < (int)image.width() && next.first >= 0 && next.second < (int)image.height() && next.second >= 0) {
  RGBAPixel * currPixel = image.getPixel(curr.first, curr.second);
  RGBAPixel * nextPixel = image.getPixel(next.first, next.second);

  return D[next.first][next.second] == -1 && closeEnough(*currPixel, *nextPixel);

} else return false;

}


vector<pair<int,int>> neighbors(pair<int,int> curr) {

  vector<pair<int,int>> n;

  // // protect against OOB indexing in D
  // if (curr.first - 1 < 0 || curr.first + 1 > image.width() || curr.second - 1 < 0 || curr.second + 1 > image.height()) {

  // }

  // initialize and add all four neighbors
  n.push_back(make_pair(curr.first - 1, curr.second));
  n.push_back(make_pair(curr.first, curr.second + 1));
  n.push_back(make_pair(curr.first + 1, curr.second));
  n.push_back(make_pair(curr.first, curr.second - 1));

  return n;
}


void rainbowRipple(PNG & image, pair<int,int> start, string sgc) {
// Color certain pixels in "image" based on their distance from "start"
// using the gaps-and-colors string "sgc" to specify the color pattern.
// The distance is determined by Breadth-First-Search which is a
// Level-Order Traversal of the tree of shortest paths from "start"
// whose edges are between good neighbors.  The neighbors of pixel
// (x,y) are (x-1,y), (x,y+1), (x+1,y), (x,y-1).  The good neighbors
// of (x,y) are those neighbors that
// 1. lie within the image,
// 2. are close to the color of pixel (x,y), and
// 3. have not been visited before.
// BFS visits "start", then the good neighbors of "start", then the
// good neighbors of these good neighbors, etc.  This forms a tree,
// level by level. The distance of a pixel from "start" is its level
// in this tree (or -1 if it hasn't been visited).  As soon as BFS
// visits a pixel it knows its distance from "start" and it can color
// the pixel based on the gaps-and-colors string "sgc".  (* However,
// it should wait to color the pixel until after its good neighbors
// are computed, since the original pixel color determines what
// neighbors are good. *)
// Coloring:
// Suppose (gap_1,color_1), (gap_2,color_2), ..., (gap_n,color_n) is the
// sequence of number,color pairs in "sgc".  Those pixels at distance
// gap_1 from "start" are colored color_1, those at distamce
// gap_1 + 1 + gap_2 are colored color_2, etc.  The gaps are the
// number of uncolored pixels between colored pixels along a shortest
// path.  The sequence specified by "sgc" should be viewed as
// repeating forever, so a pixel at distance 33 from "start" would be
// colored blue using the sequence (9,red),(4,blue),(3,green) since
// 33 = (9+1+4+1+3+1)+9+1+4.

  // initialize Queue
  Queue<pair<int, int>> BFS;

  // initialize D
  vector<vector<int>> D (image.width(), vector<int> (image.height(), -1));

  // vector<vector<int>> D;
  // vector<int> D_rows (image.width(), -1);
  // for (int i=0; i < (int)image.height()-1; i++) {
  //   D.push_back(D_rows);
  // }

  // set start to level 0
  D[start.first][start.second] = 0;

  // parse
  vector<pair<int,RGBAPixel>> vgc = parseGaps(sgc);

  // process vgc
  int vgc_length = vgc.size();
  int num_gc_pairs = vgc_length;
  vector<int> steps;
  vector<RGBAPixel> colors;
  pair<int, RGBAPixel> gc;

  for (int i = 0; i < num_gc_pairs; i++) {
    gc = vgc[i];
    steps.push_back(gc.first);
    colors.push_back(gc.second);
    vgc_length = vgc_length + gc.first;
  }

  // enqueue start
  BFS.enq(start);

  // initialize pixel pointer
  RGBAPixel * currPixl;

  pair<int, int> curr;
  vector<pair<int,int>> neighborsVect;
  pair<int, int> neighbor;

  while (!BFS.empty()) {
     curr = BFS.deq();
     neighborsVect = neighbors(curr);

     for (int i = 0; i < 4; i++) {
       neighbor = neighborsVect[i];
      
       // enq good neighbors
       if (good(image, D, curr, neighbor)) {
          BFS.enq(neighbor);
          // fill in D if neighbor hasnt been seen yet
       if (D[neighbor.first][neighbor.second] == -1) {
         D[neighbor.first][neighbor.second] = D[curr.first][curr.second] + 1;
       }
       }
     }

    // color pixel
     bool found = false;
     int reach = D[curr.first][curr.second];
     int step_count = 0;
     int path_length = steps[step_count];
     while (!found) {
       // prevent inf loop
       if (path_length > reach) {
         break;
       }
       if (reach == path_length) {
         currPixl = image.getPixel(curr.first, curr.second);
         *currPixl = colors[step_count];
         found = true;
       }
       
       // make gc string circular
       if (step_count + 1 >= num_gc_pairs) {
         step_count = 0;
       } else {
         step_count++;
       }
       path_length = path_length + 1 + steps[step_count];
     }
  }
}
