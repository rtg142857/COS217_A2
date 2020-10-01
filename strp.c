/*--------------------------------------------------------------------*/
/* strp.c */
/* Author: Alexander Menegas */
/*--------------------------------------------------------------------*/

#include "str.h"
#include <assert.h>
#include <stdio.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/

/* Calculate the length of a string pcSrc, excluding the terminating */
/* null byte ('\0'). Copied from the assignment description page. */
size_t Str_getLength(const char *pcSrc)
{
   /* Pointer for traversing the string */
   const char *pcEnd;
   assert(pcSrc != NULL);
   pcEnd = pcSrc;
   while (*pcEnd != '\0')
      pcEnd++;
   return (size_t)(pcEnd - pcSrc);
}

/* Copy the string pointed to by pcSrc, including the terminating */
/* null byte ('\0'), to the buffer pointed to by pcDest. */
/* The strings may not overlap, and the destination string pcDest */
/* must be large enough to receive the copy. */
char *Str_copy(char *pcDest, const char *pcSrc)
{
   /* Pointer for traversing the source string */
   const char *pcSrcElement;
   /* Pointer for traversing the destination string */
   char *pcDestElement;
   assert(pcSrc != NULL);
   assert(pcDest != NULL);
   pcSrcElement = pcSrc;
   pcDestElement = pcDest;
   while (*pcSrcElement != '\0')
   {
      *pcDestElement = *pcSrcElement;
      pcSrcElement++;
      pcDestElement++;
   }
   *pcDestElement = '\0';
   return pcDest;

}

/* Append the string pointed to by pcSrc to the string pointed to by */
/* pcDest. The strings may not overlap and the dest string must have */
/* enough space for the result. */
char *Str_concat(char *pcDest, const char *pcSrc)
{
   /* Length of the destination string; fill in characters after here */
   size_t uDestLength;
   /* Pointer for traversing the source string */
   const char *pcSrcElement;
   /* Pointer for filling in after the destination string */
   char *pcDestElement;
   assert(pcSrc != NULL);
   assert(pcDest != NULL);
   uDestLength = Str_getLength(pcDest);
   pcSrcElement = pcSrc;
   pcDestElement = pcDest + uDestLength;
   while (*pcSrcElement != '\0')
   {
      *pcDestElement = *pcSrcElement;
      pcSrcElement++;
      pcDestElement++;
   }
   *pcDestElement = '\0';
   return pcDest;

}

/* Compare the two strings pointed to by pcS1 and pcS2. Return an */
/* integer less than, equal to, or greater than 0 if pcS1 is found, */
/* respectively, to be less than, to match, or be greater than pcS2 */
/* using lexicographical ordering (compare the 1st character, then */
/* the second character, and so on). */
int Str_compare(const char *pcS1, const char *pcS2)
{
   /* Pointer for traversing the first string */
   const char *pcS1element;
   /* Pointer for traversing the 2nd string */
   const char *pcS2element;
   /* Integer to be returned */
   int iOrder;
   /* Condition for keeping the loop going; 0 for go, 1 for stop*/
   int iEndLoop;
   assert(pcS1 != NULL);
   assert(pcS2 != NULL);
   pcS1element = pcS1;
   pcS2element = pcS2;
   iEndLoop = 0;
   iOrder = 0;
   while (iEndLoop != 1)
      {
/* End-of-string condition when both strings are the same */
         if (*pcS1element == '\0' && *pcS2element == '\0')
         {
            iOrder = 0;
            iEndLoop = 1;
         }
         /* Activates the first time the strings are different */
         else if (*pcS1element != *pcS2element)
         {
            iOrder = (int) *pcS1element - (int) *pcS2element;
            iEndLoop = 1;
         }
         /* If the two strings have been identical up til now */
         else
         {
            pcS1element++;
            pcS2element++;
         }
      }
   return iOrder;
}

/* Find the first occurrence of the substring needle in the string */
/* haystack. The terminating null bytes ('\0') are not compared. */
/* Return a pointer to the beginning of the substring, or NULL if the */
/* substring is not found. */
char *Str_search(const char *pcHaystack, const char *pcNeedle)
{
   /* Pointer to be returned */
   const char *pc;
   /* Marking the start of the string element to be tested */
   const char *pcHStart;
   /* For comparing elements of pcHaystack */
   const char *pcHElement;
   /* For comparing elements of pcNeedle */
   const char *pcNElement;
   /* Length of the string to be found */
   size_t uNSize;
   /* For ignoring the loop if it's found */
   int iFoundIt;
   assert(pcHaystack != NULL);
   assert(pcNeedle != NULL);
   pcHStart = pcHaystack;
   pcHElement = pcHaystack;
   pcNElement = pcNeedle;
   uNSize = Str_getLength(pcNeedle);
   /* If the needle is the empty string, return the entire haystack */
   if (uNSize == 0)
   {
      pc = pcHStart;
      return (char*)pc;
   }
   iFoundIt = 0;
   pc = NULL;
   /* Check if the needle starts to match at every bit of the haystack*/
   while (*pcHStart != '\0')
   {
      /* Initially set pc to the beginning of the string */
      if (iFoundIt == 0)
      {
         pc = pcHStart;
      }
      /* Reset the comparison pointers */
      pcHElement = pcHStart;
      pcNElement = pcNeedle;
      /* Loop this when the needle matches part of the haystack */
      while (*pcHElement == *pcNElement && *pcNElement != '\0')
      {
         pcHElement++;
         pcNElement++;
         /* Success if the full needle matches */
         if (*pcNElement == '\0')
         {
            iFoundIt = 1;
         }
      }
      /* If the needle doesn't match, reset pc to null */
      if (iFoundIt == 0)
      {
         pc = NULL;
      }
      pcHStart++;
   }
   return (char*)pc;
}
