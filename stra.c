/*--------------------------------------------------------------------*/
/* stra.c */
/* Author: Alexander Menegas */
/*--------------------------------------------------------------------*/

#include "str.h"
#include <assert.h>
#include <stdio.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/

/* Calculate the length of a string pcSrc, excluding the terminating */
/* null byte ('\0'). Copied from the assignment description page. */
size_t Str_getLength(const char pcSrc[])
{
   /* Index for storing the length of the array */
   size_t uLength = 0;
   assert(pcSrc != NULL);
   while (pcSrc[uLength] != '\0')
      uLength++;
   return uLength;
}

/* Copy the string pointed to by pcSrc, including the terminating */
/* null byte ('\0'), to the buffer pointed to by pcDest[]. */
/* The strings may not overlap, and the destination string pcDest[] */
/* must be large enough to receive the copy. */
char *Str_copy(char pcDest[], const char pcSrc[])
{
   /* Index for storing the distance along pcSrc (and pcDest) */
   size_t uIndex = 0;
   assert(pcSrc != NULL);
   assert(pcDest != NULL);
   while (pcSrc[uIndex] != '\0')
   {
      pcDest[uIndex] = pcSrc[uIndex];
      uIndex++;
   }
   pcDest[uIndex] = '\0';
   return pcDest;

}

/* Append the string pcSrc[] to the string pcDest[]. The strings may */
/* not overlap and the dest string must have enough space for the */
/* result. */
char *Str_concat(char pcDest[], const char pcSrc[])
{
   /* Starting length of the string pcDest; offset by this much */
   size_t uDestLength;
   /* Index for storing the distance along pcSrc */
   size_t uIndex;
   assert(pcSrc != NULL);
   assert(pcDest != NULL);
   uDestLength = Str_getLength(pcDest);
   uIndex = 0;
   while (pcSrc[uIndex] != '\0')
   {
      pcDest[uIndex+uDestLength] = pcSrc[uIndex];
      uIndex++;
   }
   pcDest[uIndex+uDestLength] = '\0';
   return pcDest;

}

/* Compare the two strings pcS1 and pcS2. Return an integer less */
/* than, equal to, or greater than zero if pcS1 is found, */
/* respectively, to be less than, to match, or be greater than pcS2 */
/* using lexicographical ordering (compare the 1st character, then */
/* the second character, and so on). */
int Str_compare(const char pcS1[], const char pcS2[])
{
   /* Index for storing the distance along both arrays */
   size_t uIndex;
   /* Integer to be returned */
   int iOrder;
   /* Condition for keeping the loop going; 0 for go, 1 for stop */
   int iEndLoop;
   assert(pcS1 != NULL);
   assert(pcS2 != NULL);
   uIndex = 0;
   iEndLoop = 0;
   iOrder = 0;
   while (iEndLoop != 1)
      {
   /* End-of-string condition when both strings are the same */
         if (pcS1[uIndex] == '\0' && pcS2[uIndex] == '\0')
         {
            iOrder = 0;
            iEndLoop = 1;
         }
         /* Activates the first time the strings are different */
         else if (pcS1[uIndex] != pcS2[uIndex])
         {
            iOrder = (int) pcS1[uIndex] - (int) pcS2[uIndex];
            iEndLoop = 1;
         }
         /* If the two strings are identical up to the index */
         else
         {
            uIndex++;
         }
      }
   return iOrder;
}

/* Find the first occurrence of the substring pcNeedle in the string */
/* pcHaystack. The terminating null bytes ('\0') are not compared. */
/* Return a pointer to the beginning of the substring, or NULL if the */
/* substring is not found. */
char *Str_search(const char pcHaystack[], const char pcNeedle[])
{
   /* Pointer to be returned */
   const char *pc;
   /* Size of the needle, not including terminating null byte */
   size_t uNSize;
   /* Size of the haystack, not including terminating null byte */
   size_t uHSize;
   /* Index to iterate over the haystack */
   size_t uHIndex;
   /* Index to iterate over the needle */
   size_t uNIndex;
   /* For breaking the loop if it's found */
   int iFoundIt;
   assert(pcHaystack != NULL);
   assert(pcNeedle != NULL);
   uNSize = Str_getLength(pcNeedle);
   uHSize = Str_getLength(pcHaystack);
   uHIndex = 0;
   uNIndex = 0;
   iFoundIt = 0;
   /* If the needle is the empty string, return the entire haystack */
   if (uNSize == 0)
   {
      pc = &pcHaystack[0];
      return (char*)pc;
   }
   pc = NULL;
   /* Check if the needle starts to match at every bit of the haystack*/
   for (uHIndex = 0; uHIndex < uHSize; uHIndex++)
   {
   /* Initially set pc to the beginning of the substring */
      if (iFoundIt == 0)
      {
         pc = &pcHaystack[uHIndex];
      }
      /* Loop this when the needle matches part of the haystack */
      while (pcHaystack[uHIndex+uNIndex] == pcNeedle[uNIndex]
         && uNIndex < uNSize)
      {
         uNIndex++;
         /* Success if the full needle is matched */
         if (uNIndex == uNSize)
         {
            iFoundIt = 1;
         }
      }
      /* Reset the needle index when the above loop ends */
      uNIndex = 0;
      /* If the needle doesn't match, reset pc to null */
      if (iFoundIt == 0)
      {
         pc = NULL;
      }
   }
   return (char*)pc;
}






