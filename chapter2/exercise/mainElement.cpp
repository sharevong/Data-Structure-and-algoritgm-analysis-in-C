/***************************************************
* 2.19 查找数组中的主要元素（出现超过N/2次的元素）
*
***************************************************/
#include <iostream>
#include <vector>

using namespace std ;

// 判断一个元素是不是主要元素，
// 在数组元素个数为奇数时，判断最后一个元素时使用该方法
bool isMainEle( vector<int>& vec, int x )
{
	int count = 0 ;
	for( int i = 0;i < vec.size();i++ )
		if( vec[i] == x )
			count++ ;
	if( count > vec.size()/2 )
		return true ;
	return false ;
}

/* 找出数组中的主要元素
* 算法：取相邻的两个元素，如果相等则放入一个新数组中（需要考虑数组元素个数为奇数时的特殊情形）
* 原数组的主要元素显然在新数组中也会是主要元素，从而可以使用递归将问题简化
* 如果主要元素存在，返回主要元素，不存在，返回-1
* 时间复杂度：O( N )
*/
int findMain( vector<int>& vec )
{
	if( vec.empty() )   // 递归的基准情形，数组中没有元素或只有一个元素
		return -1 ;
	if( vec.size() == 1 )
		return vec[0] ;

	vector<int> tmp ;  // 新数组
	for( int i = 0;i < vec.size()-1;i += 2 )
	{
		if( vec[i+1] == vec[i] )  // 相邻元素相等时放入新数组（奇数时最后一个元素未处理）
			tmp.push_back( vec[i] ) ;		
	}

	int ret = findMain( tmp ) ;  // 递归求解新数组的主要元素

	// 当递归未找到主要元素且元素个数为奇数时，考虑最后一个元素是否是主要元素
	if( vec.size() % 2 != 0 && ret == -1 && isMainEle(vec, vec[vec.size()-1]) )
		ret = vec[vec.size()-1] ;

	return ret ;
}

int main( int argc, char** argv )
{
	int arr[9] = { 3, 3, 4, 2, 4, 4, 2, 4, 4 } ;
	vector<int> vec( arr, arr+9 ) ;
	cout << "arr: " ;
	for( int i = 0;i < vec.size();i++ )
		cout << vec[i] << " " ;
	cout << endl ;

	int mainEle = findMain( vec ) ;	
	if( mainEle == -1 )
		cout << "have no main element" << endl ;
	else
		cout << "main element is " << mainEle << endl ;
}
