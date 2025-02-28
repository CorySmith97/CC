const std = @import("std");

pub fn build(b: *std.Build) !void {
    const t = b.standardTargetOptions(.{});
    const o = b.standardOptimizeOption(.{});

    const raylib_dep = b.dependency(
        "raylib",
        .{ .target = t, .optimize = o },
    );

    const exe = b.addExecutable(.{
        .name = "Game",
        .target = t,
        .optimize = o,
    });

    exe.linkLibrary(raylib_dep.artifact("raylib"));
    exe.linkLibC();
    exe.addCSourceFiles(.{
        .root = b.path("src/"),
        .files = &[_][]const u8{
            "main.c",
            "entity.c",
            "level.c",
            "editor.c",
            "tile.c",
            "spritesheet.c",
        },
        .flags = &[_][]const u8{
            "-std=c23",
            "-Wall",
            "-Wextra",
            "-I./lib",
            "-I./assets",
        },
    });

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    // This allows the user to pass arguments to the application in the build
    // command itself, like this: `zig build run -- arg1 arg2 etc`
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    // This creates a build step. It will be visible in the `zig build --help` menu,
    // and can be selected like this: `zig build run`
    // This will evaluate the `run` step rather than the default, which is "install".
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
