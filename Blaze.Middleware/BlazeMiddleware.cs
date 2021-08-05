using System;

using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Hosting;

namespace Blaze.Middleware
{
    public class BlazeMiddleware
    {
        internal bool ShouldOptimise = false;

        public BlazeMiddleware(IWebHostEnvironment env)
        {
            ShouldOptimise = !env.IsDevelopment();
        }
    }
}
